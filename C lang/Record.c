#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum {false, true} bool;

/// STURUCTURE USED IN PROJECT
struct student
{
    int rollno;
    char name[50];
    int p_marks, c_marks;
    double per;
    char grade;
}st;

/// function to write in file
void write_student()
{
    int fd;
    system("clear");
    printf("\nPlease Enter The New Details of student \n");
    
    if ((fd = open("student.dat"/*argv[1]*/, O_WRONLY|O_APPEND|O_CREAT, 0777)) == -1)  {
	perror("Failed to create and open the file.\n");
	exit(0);
    }

    printf("\nEnter The roll number of student ");
    scanf("%d", &st.rollno);
    getchar(); // flushing buffer
    printf("\n\nEnter The Name of student ");
    scanf("%s", st.name);
    printf("\nEnter The marks in physics out of 100 : ");
    scanf("%d", &st.p_marks);
    printf("\nEnter The marks in chemistry out of 100 : ");
    scanf("%d", &st.c_marks);
    
    st.per = (st.p_marks + st.c_marks) / 2.0;
    if (st.per >= 60)
	st.grade = 'A';
    else if (st.per >= 50 && st.per<60)
        st.grade = 'B';
    else if (st.per >= 33 && st.per<50)
        st.grade = 'C';
    else
        st.grade = 'F';
   
    write(fd, (char *)&st, sizeof(st));
    close(fd);

    printf("\n\nStudent Record Has Been Created.  Press any key....   ");
    getchar();
    
}

/// function to read all records from file
void display_all()
{
    system("clear");
    int fd;
    if ((fd = open("student.dat", O_RDONLY)) == -1)  {
	perror("Failed to and open the file.\n");
	exit(0);
    }

    printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
    printf("====================================================\n");
    printf("R.No.  Name       P   C   Ave    Grade\n");
    printf("====================================================\n"); 

    lseek(fd, 0, SEEK_SET); // move offset, to find record
    while (read(fd, (char *) &st, sizeof(st))> 0)
   {      
      printf("%-6d %-10s %-3d %-3d %-3.2f  %-1c\n",
         st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
   }
    
   close(fd);
   
   printf("\n\nThis is all record.  Press any key....   ");
   getchar();
}

/// function to read specific record from file
void display_sp()
{
    int fd;
    int num;
    bool flag = false;

    system("clear");
    printf("\n\n\tPlease Enter The roll number ");
    scanf("%d", &num);

    printf("\n\n\n\t\tDISPLAY SPECIAL RECORD !!!\n\n");
    
    if ((fd = open("student.dat", O_RDONLY)) == -1)  {
	perror("Failed to and open the file.\n");
	exit(0);
    }

    lseek(fd, (st.rollno)*sizeof(st), SEEK_SET);
    while (read(fd, (char *) &st, sizeof(st))> 0)
    {
      if(st.rollno == num) {
      printf("%-6d %-10s %-3d %-3d %-3.2f  %-1c\n",
         st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
	flag = true;
	}
	if (flag == true) break;
   }
   close(fd);

   if (flag == false)
      printf("\n\nrecord not exist");
   
   printf("\n\nCommand Complete.  Press any key....   ");
   getchar();
}

/// function to modify record of file
void modify_student()
{
    int fd;
    int num;
    bool flag = false;

    system("clear");
    printf("\n\n\tPlease Enter The roll number ");
    scanf("%d", &num);
    printf("\n\n\n\t\tMODIFY RECORD !!!\n\n");

    if ((fd = open("student.dat", O_RDWR)) == -1)  {
	perror("Failed to and open the file.\n");
	exit(0);
    }

    lseek(fd, (st.rollno)*sizeof(st), SEEK_SET);
    while (read(fd, (char *) &st, sizeof(st))> 0)
   {
      if(st.rollno == num) {

	printf("\n\nEnter The New Name of student ");
	scanf("%s", st.name);
	printf("\nEnter The New marks in physics out of 100 : ");
	scanf("%d", &st.p_marks);
	printf("\nEnter The New marks in chemistry out of 100 : ");
	scanf("%d", &st.c_marks);
	
	st.per = (st.p_marks + st.c_marks) / 2.0;
	if (st.per >= 60)
	st.grade = 'A';
	else if (st.per >= 50 && st.per<60)
	st.grade = 'B';
	else if (st.per >= 33 && st.per<50)
	st.grade = 'C';
	else
	st.grade = 'F';
   
	lseek(fd, -(long)sizeof(st), 1);  // SEEK_CUR, if this not operate change SEEK_CUR
	write(fd, (char *)&st, sizeof(st));

	flag = true;
        printf("\n\n\t Record Updated \n");
	}
   }
   close(fd);

   if (flag == false)
   printf("\n\nrecord not exist");
   
   printf("\n\nCommand Complete.  Press any key....   ");
   getchar();
}

/// function to delete record of file
void delete_student()
{
   int num;
   int fd;
   int fd_tmp;
   int flag = false;
   int n;

   system("clear");
   printf("\n\n\n\tDelete Record");
   printf("\n\nPlease Enter The roll number of student You Want To Delete");
   scanf("%d", &num);

    if ((fd = open("student.dat", O_RDWR)) == -1)  {
	perror("Failed to and open the file.\n");
	exit(0);
    }

    if ((fd_tmp = open("temp.dat", O_RDWR|O_CREAT, 0777)) == -1)  {
	perror("Failed to and open the file.\n");
	exit(0);
    }
  
   // First, read all record.
   lseek(fd,0,SEEK_SET);
   while (read(fd, (char *) &st, sizeof(st))> 0)
   {
      if(st.rollno != num) { //copy all records except select num to tmp
	write(fd_tmp, (char *)&st, sizeof(st));
	}
      flag = true;
   }
   close(fd_tmp);
   close(fd);
   // remove orgin and then, rename to change
   remove("student.dat");
   rename("temp.dat", "student.dat");

   if (flag == false)
      printf("\n\nrecord not exist");
   
   printf("\n\nCommand Complete.  Press any key....  ");
   getchar();
}

/// THE MAIN FUNCTION OF PROGRAM
void main()
{
    char ch;
    int num;
    do
    {
   system("clear");
   printf("\n\n\t**1492073 Lim Ji Hun Homework**");
   printf("\n\n\t1.CREATE STUDENT RECORD");
   printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
   printf("\n\n\t3.SEARCH STUDENT RECORD ");
   printf("\n\n\t4.MODIFY STUDENT RECORD");
   printf("\n\n\t5.DELETE STUDENT RECORD");
   printf("\n\n\t6.EXIT");
   printf("\n\n\tPlease Enter Your Choice (1-6) ");
   ch = getchar();
   switch (ch)
   {
   case '1': write_student();
       break;
   case '2': display_all();
       break;
   case '3': display_sp(); break;
   case '4': modify_student(); break;
   case '5': delete_student(); break;
   case '6': break;
   default: printf("\a");
   }
    } while (ch != '6');
}