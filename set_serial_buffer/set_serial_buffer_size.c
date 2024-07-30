#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/serial.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /dev/ttyS0\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *device = argv[1];
    int fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct serial_struct serinfo;
    if (ioctl(fd, TIOCGSERIAL, &serinfo) == -1) {
        perror("TIOCGSERIAL");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Print original buffer sizes
    printf("Original output buffer size: %d bytes\n", serinfo.xmit_fifo_size);
    
    // Attempt to set a new buffer size (this may not be supported by all drivers)
    serinfo.xmit_fifo_size = 128; // Example size, adjust as needed

    if (ioctl(fd, TIOCSSERIAL, &serinfo) == -1) {
        perror("TIOCSSERIAL");
    } else {
        printf("Output buffer size set to: %d bytes\n", serinfo.xmit_fifo_size);
    }
    
    struct serial_struct serinfo_rec;
    serinfo_rec.xmit_fifo_size = 64;
    // Retrieve buffer size again to confirm changes
    if (ioctl(fd, TIOCGSERIAL, &serinfo_rec) == -1) {
        perror("TIOCGSERIAL");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("New output buffer size: %d bytes\n", serinfo_rec.xmit_fifo_size);

    close(fd);
    return 0;
}

