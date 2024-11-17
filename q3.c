#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_TEAMS 5
#define SQUAD_SIZE 20

// Struct for player age
typedef struct {
    int day;
    int month;
    int year;
} age_t;

// Struct for player detail
typedef struct {
    char name[26];     
    int kit_number;    // Unique no
    char club[21];     // Club name
    age_t dob;         // Player date of birth
    char position[21]; // Player position
} player_t;

// Struct for team details
typedef struct {
    char name[21];          // Team name
    player_t players[SQUAD_SIZE]; // Arrayy of players
    int active_size;        // No of enrolled 
} team_t;

// Global array for teams
team_t teams[NUM_TEAMS];
int team_count = 0;

// Function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(char message[]);
int calculate_age(age_t dob);
int calculate_average_age(team_t team);
int player_name_exists(char name[]);

int main() {
    int choice;

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enroll_club();
                break;
            case 2:
                add_player();
                break;
            case 3:
                search_update();
                break;
            case 4:
                display_club_statistics();
                break;
            default:
                printf("Exiting program. Goodbye!\n");
                return 0;
        }
    }
}

// Display menu
void display_menu() {
    printf("\n--- League Team Management ---\n");
    printf("1. Enroll a club\n");
    printf("2. Add a player\n");
    printf("3. Search and update a player\n");
    printf("4. Display club statistics\n");
    printf("Any other number to exit\n");
}

// Enroll a club
void enroll_club() {
    if (team_count >= NUM_TEAMS) {
        handle_error("Maximum number of clubs enrolled.");
        return;
    }

    char club_name[21];
    printf("Enter the name of the club: ");
    getchar(); // Consume newline left in the input buffer
    fgets(club_name, sizeof(club_name), stdin);
    club_name[strcspn(club_name, "\n")] = '\0'; // Remove newline

    // Check for duplicate club names
    for (int i = 0; i < team_count; i++) {
        if (strcmp(teams[i].name, club_name) == 0) {
            handle_error("Club name already exists. Please enter a unique name.");
            return;
        }
    }

    strcpy(teams[team_count].name, club_name);
    teams[team_count].active_size = 0;

    printf("Club '%s' has been successfully enrolled!\n", club_name);
    team_count++;
}

// Add a player to theeteam
void add_player() {
    if (team_count == 0) {
        handle_error("No clubs are enrolled. Please enroll a club first.");
        return;
    }

    printf("Select a club:\n");
    for (int i = 0; i < team_count; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }

    int club_choice;
    printf("Enter your choice: ");
    scanf("%d", &club_choice);

    if (club_choice < 1 || club_choice > team_count) {
        handle_error("Invalid club choice.");
        return;
    }

    if (teams[club_choice - 1].active_size >= SQUAD_SIZE) {
        handle_error("Team squad is full.");
        return;
    }

    player_t new_player;
    printf("Enter player name: ");
    getchar();
    fgets(new_player.name, sizeof(new_player.name), stdin);
    new_player.name[strcspn(new_player.name, "\n")] = '\0';

    // Check if player name exists across all th clubs
    if (player_name_exists(new_player.name)) {
        handle_error("Player with this name already exists in another club.");
        return;
    }

    printf("Enter kit number: ");
    scanf("%d", &new_player.kit_number);

    printf("Enter date of birth (dd mm yyyy): ");
    scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year);

    printf("Enter position: ");
    getchar();
    fgets(new_player.position, sizeof(new_player.position), stdin);
    new_player.position[strcspn(new_player.position, "\n")] = '\0';

    // Add player to the team
    int current_size = teams[club_choice - 1].active_size;
    strcpy(new_player.club, teams[club_choice - 1].name); // Assign club name to player
    teams[club_choice - 1].players[current_size] = new_player;
    teams[club_choice - 1].active_size++;
    printf("Player '%s' has been successfully added to '%s'.\n", new_player.name, teams[club_choice - 1].name);
}

// Search and update player
void search_update() {
    char search_name[26];
    printf("Enter player name to search: ");
    getchar();
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    for (int i = 0; i < team_count; i++) {
        for (int j = 0; j < teams[i].active_size; j++) {
            if (strcasecmp(teams[i].players[j].name, search_name) == 0) {
                printf("Player found in club '%s'.\n", teams[i].name);
                printf("Details:\n");
                printf("Name: %s, Kit Number: %d, DOB: %02d/%02d/%04d, Position: %s\n",
                       teams[i].players[j].name,
                       teams[i].players[j].kit_number,
                       teams[i].players[j].dob.day,
                       teams[i].players[j].dob.month,
                       teams[i].players[j].dob.year,
                       teams[i].players[j].position);

                printf("Update options:\n");
                printf("1. Update name\n");
                printf("2. Update kit number\n");
                printf("3. Update date of birth\n");
                printf("4. Update position\n");
                printf("5. Skip update\n");

                int update_choice;
                printf("Enter your choice: ");
                scanf("%d", &update_choice);

                switch (update_choice) {
                    case 1: {
                        printf("Enter new name: ");
                        getchar();
                        char new_name[26];
                        fgets(new_name, sizeof(new_name), stdin);
                        new_name[strcspn(new_name, "\n")] = '\0';
                        if (player_name_exists(new_name)) {
                            handle_error("Player name already exists in another club.");
                            return;
                        }
                        strcpy(teams[i].players[j].name, new_name);
                        printf("Name updated successfully.\n");
                        break;
                    }
                    case 2: {
                        printf("Enter new kit number: ");
                        int new_kit;
                        scanf("%d", &new_kit);
                        teams[i].players[j].kit_number = new_kit;
                        printf("Kit number updated successfully.\n");
                        break;
                    }
                    case 3: {
                        printf("Enter new date of birth (dd mm yyyy): ");
                        int new_day, new_month, new_year;
                        scanf("%d %d %d", &new_day, &new_month, &new_year);
                        teams[i].players[j].dob.day = new_day;
                        teams[i].players[j].dob.month = new_month;
                        teams[i].players[j].dob.year = new_year;
                        printf("Date of birth updated successfully.\n");
                        break;
                    }
                    case 4: {
                        printf("Enter new position: ");
                        getchar();
                        char new_position[21];
                        fgets(new_position, sizeof(new_position), stdin);
                        new_position[strcspn(new_position, "\n")] = '\0';
                        strcpy(teams[i].players[j].position, new_position);
                        printf("Position updated successfully.\n");
                        break;
                    }
                    case 5:
                        printf("No updates made.\n");
                        return;
                    default:
                        handle_error("Invalid choice.");
                }
                return;
            }
        }
    }
    handle_error("Player not found.");
}

// Display club statistics
void display_club_statistics() {
    printf("\n--- Club Statistics ---\n");
    for (int i = 0; i < team_count; i++) {
        printf("Club: %s, Players: %d\n", teams[i].name, teams[i].active_size);

        int average_age = calculate_average_age(teams[i]);
        printf("Average Age: %d years\n", average_age);

        for (int j = 0; j < teams[i].active_size; j++) {
            printf("  Name: %s, Kit Number: %d, DOB: %02d/%02d/%04d, Position: %s\n",
                   teams[i].players[j].name,
                   teams[i].players[j].kit_number,
                   teams[i].players[j].dob.day,
                   teams[i].players[j].dob.month,
                   teams[i].players[j].dob.year,
                   teams[i].players[j].position);
        }
        printf("\n");
    }
}

// Error handling
void handle_error(char message[]) {
    printf("Error: %s\n", message);
}

// Calculate player age
int calculate_age(age_t dob) {
    int current_year = 2024; // Assuming current year is 2024
    return current_year - dob.year;
}

// Calculate average age 
int calculate_average_age(team_t team) {
    if (team.active_size == 0) return 0;

    int total_age = 0;
    for (int i = 0; i < team.active_size; i++) {
        total_age += calculate_age(team.players[i].dob);
    }
    return total_age / team.active_size;
}

// Check if player name exists across clubs
int player_name_exists(char name[]) {
    for (int i = 0; i < team_count; i++) {
        for (int j = 0; j < teams[i].active_size; j++) {
            if (strcasecmp(teams[i].players[j].name, name) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
