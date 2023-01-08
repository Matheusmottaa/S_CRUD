#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct { 
    char title[101]; 
    unsigned pages;
    float price;  
}Book; 

typedef struct{ 
    char name[101]; 
    unsigned age; 
    Book *fvBook; 
}Student; 

Book *createBook(const char*, unsigned, float); 
void print_book(const Book*); 
void updatedBook(Book*, const char*, unsigned, float); 
void removeBook(Book**); 

Student *createStudent(Book*, const char*, unsigned); 
void print_student(const Student*); 
void updatedStudent(Student*, const char*, unsigned, Book*); 
void removeStudent(Student**); 

int main()
{ 
    
    Book *book1 = createBook("Harry Potter", 600, 125.99); 
    Student *john = createStudent(book1, "John Doe", 21); 

    printf("&book = %p, book = %p\n", &book1 , book1); 
    printf("&john = %p, john = %p\n", &john , john); 

    print_student(john); 

    putchar('\n'); 
    putchar('\n'); 

    puts("Updated student: "); 
    updatedStudent(john,"Jane Doe", 45, book1); 

    print_student(john); 

    putchar('\n'); 

    removeStudent(&john); 

    printf("&book = %p, book = %p\n", &book1 , book1); 
    printf("&john = %p, john = %p\n", &john , john); 


    return 0; 
}

Book *createBook(const char* title, unsigned pages, float price)
{ 
    Book *book = (Book*)calloc(1,sizeof(Book)); 
    strcpy(book->title, title);
    book->pages = pages; 
    book->price = price; 
    return book;  
}

void print_book(const Book *book)
{ 
    printf("title: %s, pages: %d, price: $ %.2f\n", book->title, book->pages, book->price); 
}

void updatedBook(Book *book, const char *title, unsigned pages, float price)
{ 
    strcpy(book->title, title); 
    book->pages = pages; 
    book->price = price; 
}

void removeBook(Book **book)
{ 
    free(*book); 
    *book = NULL; 
}

Student *createStudent(Book* fvb, const char* name, unsigned age)
{ 
    Student *p = (Student*)calloc(1,sizeof(Student)); 
    strcpy(p->name, name); 
    p->age = age; 
    p->fvBook = fvb; 

    return p; 
}

void print_student(const Student *p)
{ 
    printf("Name: %s, age: %d\n", p->name, p->age);
    printf("Favorite book: "); 
    print_book(p->fvBook); 
}

void updatedStudent(Student *student, const char* name, unsigned age, Book* bk)
{ 
    strcpy(student->name, name);
    student->age = age; 

    printf("Do you want updated the book of the student? (y/n): "); 
    char opt; 
    if((opt=getchar()) == 'y' || 'Y')
    { 
        
        char title[100]; 
        unsigned pages; 
        float price; 

        getchar(); 
        printf("Name: "); 
        scanf("%100[^\n]", title); 

        printf("Pages: ");
        scanf("%d", &pages); 

        printf("Price: "); 
        scanf("%f", &price); 
        
        updatedBook(student->fvBook, title, pages, price); 
        system("clear"); 
    }
}

void removeStudent(Student **p)
{   
    free((*(p))->fvBook); 
    free(*p); 
    *p = NULL; 
}