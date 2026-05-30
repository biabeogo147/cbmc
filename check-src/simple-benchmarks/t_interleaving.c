#include <assert.h>
#include <pthread.h>

int x=0, y=0;
void* t1() {
    x++;
    //y++;
}

void* t2() {
    x--;
    //y--;
}

int main(void){
    pthread_t id1, id2;
    pthread_create(&id1, NULL, t1, NULL);
    //pthread_create (&id2, NULL, t2, NULL);
    pthread_join(id1, NULL);
    //pthread_join(id2, NULL);
    return 0;
}