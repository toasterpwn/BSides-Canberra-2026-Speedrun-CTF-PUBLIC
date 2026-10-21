#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

struct user {
    char* name;
    char* password;
    float privilege_level;

    struct user* next;
};

static char flag[128];

struct user* users_head = NULL;
struct user* logged_in_user = NULL;

void add_user(char* name, char* password, float privilege_level) {
    struct user* to_insert = calloc(1, sizeof(struct user));
    
    to_insert->name = strdup(name);
    if(password != NULL) to_insert->password = strdup(password);
    to_insert->privilege_level = privilege_level;
    to_insert->next = NULL;


    struct user** next = &users_head;

    while(*next != NULL) next = &(*next)->next;

    *next = to_insert;
    printf("added user %s\n", name);
}


struct user* get_user(char* name) {
    struct user* user = users_head;

    while(user) {
        if(strcmp(user->name, name) == 0) return user;

        user = user->next;
    }

    return NULL;
}

size_t read_string(const char* prompt, char** out) {
    size_t size = 0;

    while(1) {
        printf("%s", prompt);
        if(getline(out, &size, stdin) != -1) break;

        printf("\n\nInvalid input\n");
    }

    (*out)[strcspn(*out, "\n")] = 0;

    return size;
}

void menu_list_users() {
    struct user* user = users_head;

    while(user) {
        printf("%s: %f\n", user->name, user->privilege_level);

        user = user->next;
    }
}


void menu_get_flag() {
    if(logged_in_user == NULL || logged_in_user->privilege_level < 100.0f || logged_in_user->privilege_level > 1000.0f) {
        printf("Unauthorized\n");
        return;
    }

    printf("Flag: %s\n", flag);
}



void menu_login() {
    char* username = NULL;
    char* password = NULL;

    read_string("Username: ", &username);
    read_string("Password: ", &password);


    struct user* user = get_user(username);

    if(user == NULL) {
        printf("User not found\n");
        return;
    }

    if(user->password == NULL) {
        printf("Logins to this account are disabled\n");
        return;
    }

    if(strcmp(user->password, password) == 0) {
        logged_in_user = user;
        printf("Logged in as %s\n", user->name);
    } else {
        printf("Invalid Password\n");
    }
}

void menu_logout() {
    logged_in_user = NULL;
    printf("Logged out");
}


void menu_add_user() {
    char* new_username = NULL;
    char* new_password = NULL;

    char* other_username = NULL;

    if(logged_in_user == NULL) {
        printf("Unauthorized\n");
        return;
    }

    read_string("New Username: ", &new_username);

    if(get_user(new_username) != NULL) {
        printf("Username already in use\n");
        return;
    }


    read_string("New Password: ", &new_password);

    read_string("Other Username: ", &other_username);

    float other_priv = INFINITY;
    
    struct user* other_user = get_user(other_username);
    if(other_user == NULL) other_user = logged_in_user;

    if(other_user->privilege_level > logged_in_user->privilege_level) {
        printf("Other user is higher privilege\n");
        other_priv = -INFINITY;
    } else if (other_user->privilege_level < logged_in_user->privilege_level) {
        other_priv = other_user->privilege_level;
    }
        

    float new_privilege_level = (other_priv + logged_in_user->privilege_level) / 2;

    add_user(new_username, new_password, new_privilege_level);
}

void menu() {
    printf("=== Spectrum Computing Services ===\n");
    if(logged_in_user != NULL) {
        printf("Welcome back %s!", logged_in_user->name);

        printf(
            "\n"
            "Options: \n"
            " o> Logout \n"
            " a> Add User\n"
            " s> List Users\n"
            " f> Get Flag\n"
            " x> exit\n"
        );
    } else {
        printf(
            "Demo Account: user1:user1\n"
            "\n"
            "Options: \n"
            " l> login \n"
            " s> list users\n"
            " x> exit\n"
        );
    }

    char* line = NULL;
    size_t line_size = 0;

    while(1) {
        printf("Option? ");

        if(getline(&line, &line_size, stdin) == -1) continue;


        switch(line[0]) {
            case 'l': menu_login(); break;
            case 'o': menu_logout(); break;
            case 'a': menu_add_user(); break;
            case 'f': menu_get_flag(); break;
            case 's': menu_list_users(); break;
            case 'x': printf("Thank you for using spectrum computing services. Goodbye.\n"); exit(0); break;
            default:
                printf("Invalid option\n");
                continue;
        }

        break;
    }
    
    
}



void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  FILE* f = fopen("flag.txt", "r");
  fgets(flag, sizeof(flag), f);
  fclose(f);
}

int main() {
    setup();
    add_user("admin", NULL, 500.0f);
    add_user("user1", "user1", 50.0f);
    add_user("anon", "", 0);
    
    
    while(1) 
        menu();


}