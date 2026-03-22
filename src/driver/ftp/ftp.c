#include <stdio.h>
#include <string.h>

void ftp_init(void) { printf("[FTP] Initialized\n"); }

void ftp_connect(const char *host, const char *user) {
    printf("\n=== FTP Connect ===\n");
    printf("Host: %s\n", host);
    printf("User: %s\n", user);
    printf("Connected!\n");
    printf("====================\n\n");
}

void ftp_list(void) {
    printf("\n=== FTP List ===\n");
    printf("drwxr-xr-x  2 user 100 4096 ./\n");
    printf("drwxr-xr-x  2 user 100 4096 ../\n");
    printf("-rw-r--r--  1 user 100 1234 file1.txt\n");
    printf("-rw-r--r--  1 user 100 5678 file2.jpg\n");
    printf("drwxr-xr-x  2 user 100 4096 documents/\n");
    printf("======================\n\n");
}

void ftp_upload(const char *local, const char *remote) {
    printf("\n=== FTP Upload ===\n");
    printf("Local: %s\n", local);
    printf("Remote: %s\n", remote);
    printf("Uploading...\n");
    printf("████████████ 100%%\n");
    printf("Done!\n");
    printf("====================\n\n");
}

void ftp_download(const char *remote, const char *local) {
    printf("\n=== FTP Download ===\n");
    printf("Remote: %s\n", remote);
    printf("Local: %s\n", local);
    printf("Downloading...\n");
    printf("████████████ 100%%\n");
    printf("Done!\n");
    printf("====================\n\n");
}

void ftp_delete(const char *file) {
    printf("[FTP] Deleted: %s\n", file);
}

void ftp_test(void) {
    printf("\n=== FTP Test ===\n");
    ftp_init();
    ftp_connect("ftp.example.com", "user");
    ftp_list();
    ftp_upload("local.txt", "/remote.txt");
    ftp_download("/remote.txt", "local.txt");
    printf("==================\n\n");
}
