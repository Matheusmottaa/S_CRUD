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
Book *copyBook(const Book*); 
void print_book(const Book*); 
void updatedBook(Book*, const char*, unsigned, float); 
void removeBook(Book**); 

Student *createStudent(const char*, unsigned, const Book*); 
void print_student(const Student*); 
void updatedStudent(Student*, const char*, unsigned); 
void removeStudent(Student**); 

int main()
{ 
    Book *book1 = createBook("Harry Potter", 600, 125.99); 
    Student *student = createStudent("John Doe", 21, book1); 
    printf("&student = %p, student = %p\n", &student , student); 

    print_student(student); 
    putchar('\n'); 
    putchar('\n'); 

    updatedStudent(student,"Jane Doe", 45); 
    print_student(student); 
    putchar('\n'); 

    removeStudent(&student); 

    printf("&student = %p, student = %p\n", &student, student); 

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

Book *copyBook(const Book* bk)
{ 
    return createBook(bk->title, bk->pages, bk->price); 
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
    Book *bk = *book; 
    free(bk); 
    *book = NULL; 
}

Student *createStudent(const char* name, unsigned age, const Book *bk)
{ 
    Student *p = (Student*)calloc(1,sizeof(Student)); 
    strcpy(p->name, name); 
    p->age = age; 
    p->fvBook = copyBook(bk); 
    return p; 
}

void print_student(const Student *p)
{ 
    printf("Name: %s, age: %d\n", p->name, p->age);
    printf("Favorite book: "); 
    print_book(p->fvBook); 
}

void updatedStudent(Student *student, const char* name, unsigned age)
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

void removeStudent(Student **student)
{   
    removeBook(&(*student)->fvBook); 
    free(*student); 
    *student = NULL; 
}