#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    std::string srcFile, destFile;
    off_t srcOffset, destOffset;
    size_t bytesToCopy;
    std::cout << "Enter the name of the source file: ";
    std::cin >> srcFile;
    std::cout << "Enter the name of the destination file: ";
    std::cin >> destFile;
    std::cout << "Enter the initial offset in the source file (in bytes): ";
    std::cin >> srcOffset;
    std::cout << "Enter the initial offset in the destination file (in bytes): ";
    std::cin >> destOffset;
    std::cout << "Enter the number of bytes to copy: ";
    std::cin >> bytesToCopy;
    int srcFd = open(srcFile.c_str(), O_RDONLY);
    if (srcFd == -1)
    {
        perror("Failed");
        return 1;
    }
    int destFd = open(destFile.c_str(), O_WRONLY);
    if (destFd == -1)
    {
        close(srcFd);
        perror("Failed");
        return 1;
    }
    if (lseek(srcFd, srcOffset, SEEK_SET) == -1)
    {
        close(srcFd);
        close(destFd);
        perror("Failed");
        return 1;
    }
    if (lseek(destFd, destOffset, SEEK_SET) == -1)
    {
        close(srcFd);
        close(destFd);
        perror("Failed");
        return 1;
    }
    char dataBuffer[BUFSIZ];
    ssize_t bytesRead, bytesWritten;
    while (bytesToCopy > 0)
    {
        size_t chunkSize = std::min(bytesToCopy, sizeof(dataBuffer));
        bytesRead = read(srcFd, dataBuffer, chunkSize);
        if (bytesRead == -1)
        {
            close(srcFd);
            close(destFd);
            perror("Failed");
            return 1;
        } 
        else if (bytesRead == 0)
        {
            break; 
        }
        bytesWritten = write(destFd, dataBuffer, bytesRead);
        if (bytesWritten == -1)
        {
            close(srcFd);
            close(destFd);
            perror("Failed");
            return 1;
        }
        bytesToCopy -= bytesWritten;
    }
    close(srcFd);
    close(destFd);
    std::cout << "Successfully copied " << bytesToCopy << " bytes from the source file to the destination file.\n";
    return 0;
}
