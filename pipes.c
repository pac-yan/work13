#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  int parent[2];
  int child[2];
  pipe(parent);
  pipe(child);
  int f = fork();
  if (f == 0) {
/*-------------code for the child ---------------------*/
    close(parent[WRITE]);
    close(child[READ]);
    int toMath;
    read(parent[READ], &toMath, sizeof(toMath));
    printf("child is doing math on: %d\n", toMath);
    toMath = toMath/2 + 300;
    write(child[WRITE], &toMath, sizeof(toMath));
  }
  else {
/*-------------code for the parent ---------------------*/
    close(child[WRITE]);
    close(parent[READ]);
    int number = 50;
    write(parent[WRITE], &number, sizeof(number));
    printf("parent sent: %d\n", number);
    read(child[READ], &number, sizeof(number));
    printf("parent received: %d\n", number );
  }
  return 0;
}
