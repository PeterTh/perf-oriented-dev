#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void find_largest_file(char *dir_path, long long *max_size, char *max_file);

int main() {
    long long max_size = 0;
    char max_file[256] = "";

    // Start the search in the current directory
    find_largest_file(".", &max_size, max_file);

    // Print the name of the largest file
    printf("The largest file is %s with size %lld bytes\n", max_file, max_size);

    return 0;
}

void find_largest_file(char *dir_path, long long *max_size, char *max_file) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char file_path[512];

    // Open the directory
    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Loop through all the files in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        // Build the path to the file
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
        // Get information about the file
        if (stat(file_path, &file_stat) == -1) {
            perror("Error getting file stat");
            continue;
        }
        // If it's a regular file and larger than the current maximum, update the maximum
        if (S_ISREG(file_stat.st_mode) && file_stat.st_size > *max_size) {
            *max_size = file_stat.st_size;
            strcpy(max_file, file_path);
        }
        // If it's a directory, recursively search it for the largest file
        if (S_ISDIR(file_stat.st_mode)) {
            find_largest_file(file_path, max_size, max_file);
        }
    }

    closedir(dir);
}
