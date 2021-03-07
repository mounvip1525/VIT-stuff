//Implementing reader writer using monitors
#include <iostream> 
#include <pthread.h> 
#include <unistd.h> 
using namespace std; 
  
class monitor { 
private: 
    int readerCount,writerCount,waitReader,waitWriter; 
    pthread_cond_t canread; 
    pthread_cond_t canwrite; 
    pthread_mutex_t condlock; 
  
public: 
    monitor() 
    { 
        readerCount = writerCount = waitReader = waitWriter = 0; 
        pthread_cond_init(&canread, NULL); 
        pthread_cond_init(&canwrite, NULL); 
        pthread_mutex_init(&condlock, NULL); 
    } 
    void beginread(int i) 
    { 
        pthread_mutex_lock(&condlock); 
        if (writerCount == 1 || waitWriter > 0) { 
            waitReader++; 
            pthread_cond_wait(&canread, &condlock); 
            waitReader--; 
        } 
        readerCount++; 
        cout << "reader " << i << " is reading\n"; 
        pthread_mutex_unlock(&condlock); 
        pthread_cond_broadcast(&canread); 
    } 
  
    void endread(int i) 
    { 
        pthread_mutex_lock(&condlock); 
  
        if (--readerCount == 0) 
            pthread_cond_signal(&canwrite); 
  
        pthread_mutex_unlock(&condlock); 
    } 
  
    void beginwrite(int i) 
    { 
        pthread_mutex_lock(&condlock); 
        if (writerCount == 1 || readerCount > 0) { 
            ++waitWriter; 
            pthread_cond_wait(&canwrite, &condlock); 
            --waitWriter; 
        } 
        writerCount = 1; 
        cout << "writer " << i << " is writing\n"; 
        pthread_mutex_unlock(&condlock); 
    } 
  
    void endwrite(int i) 
    { 
        pthread_mutex_lock(&condlock); 
        writerCount = 0; 
        if (waitReader > 0) 
            pthread_cond_signal(&canread); 
        else
            pthread_cond_signal(&canwrite); 
        pthread_mutex_unlock(&condlock); 
    } 
} 
M; 
  
void* reader(int* id) 
{ 
    int c = 0; 
    int i = (int)id; 
    while (c < 5) { 
        usleep(1); 
        M.beginread(i); 
        M.endread(i); 
        c++; 
    } 
} 
  
void* writer(int* id) 
{ 
    int c = 0; 
    int i = (int)id; 
    while (c < 5) { 
        usleep(1); 
        M.beginwrite(i); 
        M.endwrite(i); 
        c++; 
    } 
} 
  
int main() 
{ 
    pthread_t r[5], w[5]; 
    int id[5]; 
    for (int i = 0; i < 5; i++) { 
        id[i] = i; 
        pthread_create(&r[i], NULL, &reader, &id[i]); 
        pthread_create(&w[i], NULL, &writer, &id[i]); 
    } 
  
    for (int i = 0; i < 5; i++) { 
        pthread_join(r[i], NULL); 
    } 
    for (int i = 0; i < 5; i++) { 
        pthread_join(w[i], NULL); 
    } 
}
