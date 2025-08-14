#include <stdio.h>
#include <unistd.h>

#define SECTOR_SIZE 512
#define FILE_SIZE (20 * 1024 * 1024) 

int main(int argc, char **argv){
  
  if( argc != 2 ) {
    printf("Usage: %s /path/to/file\n", argv[0]);
    return 1;
  } 
  
  const char *filepath = argv[1];
  printf("Entered: %s\n", filepath);
  printf("Trying to open the file...\n");

  FILE *fp = fopen(filepath, "rb");
  
  if(fp) { 
    
    printf("File exists! Opening it...\n");
    fclose(fp);
    fp = fopen(filepath, "rb+");
    if( !fp){
      perror("Error creating the file");
      return 1;
    }

  } else {
      printf("The file doesn't exist. Creating it...\n");
      fp = fopen(filepath, "wb+");
      if ( !fp ) {
        perror("Error creating the file");
        return 1; 
      }
      
      if (ftruncate(fileno(fp), 20 * 1024 * 1024) != 0) {
        printf("Error setting file size.\n");
        fclose(fp);
        return 1;
    }

    printf("File of size 20 MB created succesfully. \n");
  }

  fclose(fp);
  return 0;
}
