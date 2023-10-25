/*Md Eyashin*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Structer for Admine*/
struct login
{
    char uname_admin[20];
    char password_admin[15];

}ad;


/*Structer for Receptionist*/
struct login_r
{
    char uname[20];
    char password[15];

}recep;

/*Structer for doctor(Admin)*/
struct DOCTOR
{
    char id[15];
    char name[40];
    int age;
    char gender[10];
    char cNumber[15];
    char department[50];
} doc;


//Staff Document
struct Staff
{
    char id[15];
    char name[40];
    int age;
    char gender[10];
    char cNumber[15];
    char address[50];
} staff;


/*Structer for doctor(Admin)*/
struct reception
{
    char id[15];
    char pname[40];
    char dname[40];
    int age;
    char gender[10];
    char cNumber[15];
    char entry_time[20];
}recept;


/*start
    Admin
        code
            for
                login & register*/

/*Register login page for admin*/
void register_page()
{
    FILE *file;
    file = fopen("admin.txt","w");
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t***************************ADMINE REGISTER PAGE*************************\n\n\n\n");
    printf("\t\t\t\t\tUsername: ");
    scanf("%s",ad.uname_admin);
    printf("\t\t\t\t\tPassword: ");
    scanf("%s",ad.password_admin);
    fprintf(file,"Username:%s\nPassword:%s\n\n\n\n",ad.uname_admin, ad.password_admin);
    fclose(file);
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n");
    printf("\n\n\n\n\n\t\t\t\t\tRegistetion successfully.\n\n\n\n\n");
    printf("\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");
    system("pause");
    system("cls");
    login_page();

}

/*Admin login page*/
void login_page()
{
    FILE *file;
    char user[15];
    char pass[20];
    file = fopen("admin.txt","r+");

    fscanf(file,"Username:%s\nPassword:%s\n",ad.uname_admin, ad.password_admin);


    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t****************************ADMINE LOGIN PAGE***************************\n\n\n\n");
    printf("\t\t\t\t\tUsername: ");
    scanf("%s",&user);
    printf("\t\t\t\t\tPassword: ");
    scanf("%s",&pass);

    if(strcmp(ad.uname_admin,user)==0 && strcmp(ad.password_admin,pass)==0)
    {
        system("cls");                                                    //Admine page login successfully
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\tLogin successfully.");
        system("pause");
        system("cls");
        home_page_of_admin();                                                           //Exit in the code

    }
    else
    {
        printf("\n\n\n\t\t\tYour username or password are wrong.Please try agin.");
        system("pause");
        system("cls");
        admine();
    }

    fclose(file);

}

/*Create form of doctor page(Admin)*/
void c_doctor_f()
{
    system("cls");
    FILE *d;
    fflush(stdin);
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t*********************Create Form for Doctor(ADMINE)*********************\n\n\n\n");
    d=fopen("doctor.txt","a");
    printf("\t\t\t\t\tID:\t\t");
    gets(doc.id);
    printf("\t\t\t\t\tName:\t\t");
    gets(doc.name);
    printf("\t\t\t\t\tAge:\t\t");
    scanf("%d",&doc.age);
    fflush(stdin);
    printf("\t\t\t\t\tGender:\t\t");
    gets(doc.gender);
    printf("\t\t\t\t\tContact Number:\t");
    gets(doc.cNumber);
    printf("\t\t\t\t\tDepartment:\t");
    gets(doc.department);
    fprintf(d,"Id\t\t:%s\nNAME\t\t:%s\nAGE\t\t:%d\nGENDER\t\t:%s\nCONTACT NUMBER\t:%s\nDEPARTMENT\t:%s\n\n\n",doc.id,doc.name,doc.age,doc.gender,doc.cNumber,doc.department);
    fclose(d);

    printf("\n\t\t\tDo you continue! If,NO it is then enter 0 OR YES it is,then enter any number: ");
    int number;
    scanf("%d",&number);

    if(number==0)
        doctor_p();
    else
        c_doctor_f();


}


/* Edit doctor information */
/*Md Eyashin*/
void edit_d_i() {
    char idToEdit[15];
    printf("Enter the ID of the doctor you want to edit: ");
    scanf("%s", idToEdit);

    FILE *file = fopen("doctor.txt", "r+");
    if (file == NULL) {
        printf("Error opening file for editing.\n");
        return;
    }

    int found = 0;
    while (fread(&doc, sizeof(doc), 1, file) == 1) {
        // Trim whitespace from the ID before comparison
        char trimmedID[15];
        sscanf(doc.id, "%s", trimmedID);

        if (strcmp(idToEdit, trimmedID) == 0) {
            found = 1;
            printf("Editing Doctor ID: %s\n", doc.id);

            // You can add code here to modify specific fields of the doctor record
            printf("Enter new name: ");
            scanf("%s", doc.name);

            // Update the record in the file
            fseek(file, -sizeof(doc), SEEK_CUR);
            fwrite(&doc, sizeof(doc), 1, file);
            printf("Doctor information updated successfully.\n");
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Doctor with ID %s not found.\n", idToEdit);
    }
}

/* Delete doctor information */
void delete_d_i() {
    char idToDelete[15];
    printf("Enter the ID of the doctor you want to delete: ");
    scanf("%s", idToDelete);

    FILE *file = fopen("doctor.txt", "r");
    if (file == NULL) {
        printf("Error opening file for deletion.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating a temporary file for deletion.\n");
        fclose(file);
        return;
    }

    int found = 0;
    while (fread(&doc, sizeof(doc), 1, file) == 1) {
        // Trim whitespace from the ID before comparison
        char trimmedID[15];
        sscanf(doc.id, "%s", trimmedID);

        if (strcmp(idToDelete, trimmedID) == 0) {
            found = 1;
            printf("Deleting Doctor ID: %s\n", doc.id);
        } else {
            fwrite(&doc, sizeof(doc), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Doctor with ID %s not found.\n", idToDelete);
    } else {
        remove("doctor.txt");
        rename("temp.txt", "doctor.txt");
        printf("Doctor information deleted successfully.\n");
    }
}


/*All information of doctor*/
void a_i_doctor()
{
    system("cls");
    char read;
    int i;
    printf("\n\n**********************************************************************************************************************\n");
    printf("******************************************All DOCTOR INFORMSTIONPAGE(ADMINE)******************************************\n\n\n\n");
    FILE *d;
    d=fopen("doctor.txt","r+");

    while(1)
    {
        read=fgetc(d);
        if(read==EOF)
            break;
        printf("%c",read);
    }

    fclose(d);
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t1.Edit Information\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t2.Delete Information\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t3.Back to Doctor page\n");
    printf("**********************************************************************************************************************\n");
    printf("**********************************************************************************************************************\n\n");

    while(1)
    {
        int choice;
        printf("\t\t\t\t\t\t\t\t\t\t\tPlease enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            edit_d_i();             //Edit Doctor information
            break;
        case 2:
            delete_d_i();           //Delete doctor information
            break;
        case 3:
            doctor_p();             //Back to doctor page
            break;
        default:
        {
            system("cls");
            a_i_doctor();           //Again show all information of doctor

        }
        }
    }

}




/*Back to Homepage(Admin)*/
void b_homepage()
{
    system("cls");
    home_page_of_admin();
}


/*Doctor page(Admin)*/
void doctor_p()
{
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t**************************DOCTOR PAGE(ADMINE)***************************\n\n\n\n\n");
    printf("\t\t\t\t\t\t1.All Information of Doctor\n");
    printf("\t\t\t\t\t\t2.Create form of Doctor\n");
    printf("\t\t\t\t\t\t3.Back to Homepage\n\n\n\n");
    printf("\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");
    while(1)
    {
        int choice;
        printf("\t\t\tPlease your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            a_i_doctor();               //All information of doctor page
            break;
        case 2:
            c_doctor_f();               //Create doctor form page
            break;
        case 3:
            b_homepage();               //Back homepage(Admin)
            break;
        default:
        {
            system("cls");
            printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
            printf("\t\t\t**************************DOCTOR PAGE(ADMINE)***************************\n\n\n\n");
            printf("\t\t\t\t\t\t1.All Information of Doctor\n");
            printf("\t\t\t\t\t\t2.Create form of Doctor\n");
            printf("\t\t\t\t\t\t3.Back to Homepage\n\n\n\n");
            printf("\t\t\t************************************************************************\n");
            printf("\t\t\t************************************************************************\n\n");
            printf("\t\t\tYour choice is WRONG.Please choice right option.\n");
        }

        }
    }
}




/*ADMINE page*/
void admine()
{
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t******************************ADMINE PAGE*******************************\n\n\n");
    printf("\n\t\t\t\t\t\t\t1.Login\n");
    printf("\t\t\t\t\t\t\t2.Sign-up\n\n\n");
    printf("\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");


    while(1)
    {
        int choise;
        printf("\t\t\tPlease enter your choise: ");
        scanf("%d",&choise);
        system("cls");  //clear screen

        switch(choise)
        {
        case 1:
            login_page();
            break;
        case 2:
            register_page();
            break;
        default :
        {

            printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
            printf("\t\t\t******************************ADMINE PAGE*******************************\n\n\n");
            printf("\n\t\t\t\t\t\t\t1.Login\n");
            printf("\t\t\t\t\t\t\t2.Sign-up\n\n\n");
            printf("\n\t\t\t************************************************************************\n");
            printf("\t\t\t************************************************************************\n\n");
            printf("\t\t\tYour choise is WRONG.Please right choise.\n");
        }
        }

    }
}


/*Admin
    main
        function(Homepage)*/
void home_page_of_admin()
{
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t**************************HOME PAGE OF ADMINE***************************\n\n\n");
    printf("\n\t\t\t\t\t\t1.Doctor\n");
    printf("\t\t\t\t\t\t2.Patient\n");
    printf("\t\t\t\t\t\t3.Staff\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t4.EXIT\n");
    printf("\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");
    while(1)
    {
        int choice;
        printf("\t\t\tPlease your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            doctor_p();
            break;
        case 2:
            patient_p();
            break;
        case 3:
            staff_p();
            break;
        case 4:
            system("cls");
            exit(1);
        default:
        {
            system("cls");
            printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
            printf("\t\t\t**************************HOME PAGE OF ADMINE***************************\n\n\n");
            printf("\n\t\t\t\t\t\t1.Doctor\n");
            printf("\t\t\t\t\t\t2.Patient\n");
            printf("\t\t\t\t\t\t3.Staff\n\n\n");
            printf("\t\t\t\t\t\t\t\t\t\t4.EXIT\n");
            printf("\t\t\t************************************************************************\n");
            printf("\t\t\t************************************************************************\n\n");
            printf("\t\t\tYour choice is WRONG.Please choice right option.\n");
        }

        }

    }

}


/*start
    patient
        information
            code(admin)*/

/*Patient page(Admin)*/
void patient_p()
{
    system("cls");
    char read;
    int i;
    printf("\n\n**********************************************************************************************************************\n");
    printf("******************************************All PATIENT INFORMSTIONPAGE(ADMINE)*****************************************\n\n\n\n");
    FILE *d;
    d=fopen("patient.txt","r+");

    while(1)
    {
        read=fgetc(d);
        if(read==EOF)
            break;
        printf("%c",read);
    }

    fclose(d);
    printf("\n\n");
    printf("**********************************************************************************************************************\n");
    printf("**********************************************************************************************************************\n\n");
    system("pause");
    system("cls");
    home_page_of_admin();
}





/*start
    Receptionist
        code
            for
                All information*/

/*RECEPTIONIST page*/
void receptionist()
{
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t***************************RECEPTIONIST PAGE****************************\n\n\n");
    printf("\n\t\t\t\t\t\t\t1.Login\n");
    printf("\t\t\t\t\t\t\t2.Sign-up\n\n\n");
    printf("\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");


    while(1)
    {
        int choise;
        printf("\t\t\tPlease enter your choise: ");
        scanf("%d",&choise);
        system("cls");  //clear screen

        switch(choise)
        {
        case 1:
            login_page_r();
            break;
        case 2:
            register_page_r();
            break;
        default :
        {

            printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
            printf("\t\t\t***************************RECEPTIONIST PAGE****************************\n\n\n");
            printf("\n\t\t\t\t\t\t\t1.Login\n");
            printf("\t\t\t\t\t\t\t2.Sign-up\n\n\n");
            printf("\n\t\t\t************************************************************************\n");
            printf("\t\t\t************************************************************************\n\n");
            printf("\t\t\tYour choise is WRONG.Please right choise.\n");
        }
        }

    }
}


/*Register login page for Receptionist*/
void register_page_r()
{
    FILE *file;
    file = fopen("receotionist.txt","a");
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************RECEPTIONIST REGISTER PAGE**********************\n\n\n\n");
    printf("\t\t\t\t\tUsername: ");
    scanf("%s",recep.uname);
    printf("\t\t\t\t\tPassword: ");
    scanf("%s",recep.password);
    fprintf(file,"Username:%s\nPassword:%s\n",recep.uname, recep.password);
    fclose(file);
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n");
    printf("\n\n\n\n\n\t\t\t\t\tRegistetion successfully.\n\n\n\n\n");
    printf("\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");
    system("pause");
    system("cls");
    login_page_r();

}

/*Receptionist login page*/
/*Md Eyashin*/
void login_page_r()
{
    FILE *file;
    char user[15];
    char pass[20];
    file = fopen("receotionist.txt","r+");

    fscanf(file,"Username:%s\nPassword:%s\n",recep.uname, recep.password);


    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t*************************RECEPTIONIST LOGIN PAGE************************\n\n\n\n");
    printf("\t\t\t\t\tUsername: ");
    scanf("%s",&user);
    printf("\t\t\t\t\tPassword: ");
    scanf("%s",&pass);

    if(strcmp(recep.uname,user)==0 && strcmp(recep.password,pass)==0)
    {
        system("cls");                                                    //Receptionist page login successfully
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\tLogin successfully.");
        system("pause");
        system("cls");
        r_c_patient_from();
    }
    else
    {
        printf("\n\n\n\t\t\tYour username or password are wrong.Please try agin.");
        system("pause");
        system("cls");
        receptionist();
    }

    fclose(file);

}

/*Home page of Receptionist*/
void r_c_patient_from()
{
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************HOME PAGE OF RECEPTIONIST***********************\n\n\n");
    printf("\n\t\t\t\t\t\t1.Creat patient from\n");
    printf("\t\t\t\t\t\t2.Exit\n\n\n\n");
    printf("\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");
    while(1)
    {
        int choice;
        printf("\t\t\tPlease your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            c_patient_f();          //create patient from
            break;
        case 2:
            system("cls");          //Exit the code
            exit(1);
        default:
        {
            system("cls");
            printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
            printf("\t\t\t************************HOME PAGE OF RECEPTIONIST***********************\n\n\n");
            printf("\n\t\t\t\t\t\t1.Creat patient from\n");
            printf("\t\t\t\t\t\t2.Exit\n\n\n\n");
            printf("\t\t\t************************************************************************\n");
            printf("\t\t\t************************************************************************\n\n");
            printf("\t\t\tYour choice is WRONG.Please choice right option.\n");
        }

        }

    }

}


/*Create form of patient page(receptionist)*/
void c_patient_f()
{
    system("cls");
    FILE *d;
    fflush(stdin);
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t******************Create Form for Patient(RECEPTIONIST)*****************\n\n\n\n");
    d=fopen("patient.txt","a");
    printf("\t\t\t\t\tID\t\t:");
    gets(recept.id);
    printf("\t\t\t\t\tPatient Name\t:");
    gets(recept.pname);
    printf("\t\t\t\t\tDoctor Name\t:");
    gets(recept.dname);
    printf("\t\t\t\t\tAge\t\t:");
    scanf("%d",&recept.age);
    fflush(stdin);
    printf("\t\t\t\t\tGender\t\t:");
    gets(recept.gender);
    printf("\t\t\t\t\tContact Number\t:");
    gets(recept.cNumber);
    printf("\t\t\t\t\tEntry Time\t:");
    gets(recept.entry_time);
    fprintf(d,"Id\t\t:%s \nPATIENT NAME\t:%s \nDOCTOR NAME\t:%s \nAGE\t\t:%d \nGENDER\t\t:%s \nCONTACT NUMBER\t:%s \nENTRY TIME\t:%s\n\n\n",recept.id,recept.pname,recept.dname,recept.age,recept.gender,recept.cNumber,recept.entry_time);
    fclose(d);

    printf("\n\t\t\tDo you continue! If,NO it is then enter 0 OR YES it is,then enter any number: ");
    int number;
    scanf("%d",&number);

    if(number==0)
    {
        system("cls");
        r_c_patient_from();
    }
    else
    {
        system("cls");
        c_patient_f();
    }

}



/*All information of staff*/
void a_i_staff()
{
    system("cls");
    char read;
    int i;
    printf("\n\n**********************************************************************************************************************\n");
    printf("*******************************************All STAFF INFORMSTIONPAGE(ADMINE)******************************************\n\n\n\n");
    FILE *d;
    d=fopen("staff.txt","r+");

    while(1)
    {
        read=fgetc(d);
        if(read==EOF)
            break;
        printf("%c",read);
    }

    fclose(d);
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t1.Edit Information\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t2.Delete Information\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t3.Back to Staff page\n");
    printf("**********************************************************************************************************************\n");
    printf("**********************************************************************************************************************\n\n");

    while(1)
    {
        int choice;
        printf("\t\t\t\t\t\t\t\t\t\t\tPlease enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            edit_s_i();             //Edit Staff information
            break;
        case 2:
            delete_s_i();           //Delete staff information
            break;
        case 3:
            staff_p();             //Back to staff page
            break;
        default:
        {
            system("cls");
            a_i_staff();           //Again show all information of staff

        }
        }
    }

}


/*Create form of Staff page(Admin)*/
void c_staff_f()
{
    system("cls");
    FILE *d;
    fflush(stdin);
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t**********************Create Form for Staff(ADMINE)*********************\n\n\n\n");
    d=fopen("staff.txt","a");
    printf("\t\t\t\t\tID:\t\t");
    gets(staff.id);
    printf("\t\t\t\t\tName:\t\t");
    gets(staff.name);
    printf("\t\t\t\t\tAge:\t\t");
    scanf("%d", &staff.age);
    fflush(stdin);
    printf("\t\t\t\t\tGender:\t\t");
    gets(staff.gender);
    printf("\t\t\t\t\tContact Number:\t");
    gets(staff.cNumber);
    printf("\t\t\t\t\tAddress:\t");
    gets(staff.address);
    fprintf(d,"Id\t\t:%s \nNAME\t\t:%s \nAGE\t\t:%d \nGENDER\t\t:%s \nCONTACT NUMBER\t:%s \nADDRESS\t\t:%s\n\n\n",staff.id,staff.name,staff.age,staff.gender,staff.cNumber,staff.address);
    fclose(d);

    printf("\n\t\t\tDo you continue! If,NO it is then enter 0 OR YES it is,then enter any number: ");
    int number;
    scanf("%d",&number);

    if(number==0)
        staff_p();
    else
        c_staff_f();


}


// Function to edit staff information
void edit_s_i()
{
    char idToEdit[15];
    printf("Enter the ID of the staff you want to edit: ");
    scanf("%s", idToEdit);

    FILE *file = fopen("staff.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file for editing.\n");
        return;
    }


    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating a temporary file for editing.\n");
        fclose(file); // Close the original file
        return;
    }

    int found = 0;

    while (fscanf(file, "Id\t\t:%s", staff.id) != EOF)
    {
        if (strcmp(staff.id, idToEdit) == 0)
        {
            found = 1;
            printf("Enter updated information:\n");
            printf("Name:\t");
            fflush(stdin);
            gets(staff.name);
            fflush(stdin);
            printf("Age:\t");
            scanf("%d", &staff.age);
            fflush(stdin);
            printf("Gender:\t");
            gets(staff.gender);
            printf("Contact Number:\t");
            gets(staff.cNumber);
            printf("Address:\t");
            gets(staff.address);
        }

        // Print the staff record to the temporary file
        fprintf(tempFile, "Id\t\t:%s \nNAME\t\t:%s \nAGE\t\t:%d \nGENDER\t\t:%s \nCONTACT NUMBER\t:%s \nADDRESS\t\t:%s\n\n\n",
                staff.id, staff.name, staff.age, staff.gender, staff.cNumber, staff.address);
        break;
    }

    fclose(file);
    fclose(tempFile); // Close the temporary file
    /*Md Eyashin*/

    if (!found)
    {
        printf("Staff with ID %s not found.\n", idToEdit);
    }
    else
    {
        if (remove("staff.txt") == 0)
        {
            if (rename("temp.txt", "staff.txt") == 0)
            {
                printf("Staff information updated successfully.\n");
            }
            else
            {
                printf("Error renaming the temporary file.\n");
            }
        }
        else
        {
            printf("Error deleting the original file.\n");
        }
    }
}

// Function to delete staff information
void delete_s_i()
{
    char idToDelete[15];
    printf("Enter the ID of the staff you want to delete: ");
    scanf("%s", idToDelete);

    FILE *file = fopen("staff.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file for deletion.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating a temporary file for deletion.\n");
        fclose(file); // Close the original file
        return;
    }

    int found = 0;
    struct Staff staff;

    while (fscanf(file, "Id\t\t:%s", staff.id) != EOF)
    {
        if (strcmp(staff.id, idToDelete) == 0)
        {
            found = 1;
            // Skip this staff record (do not write to the temporary file)
            char buffer[1000];
            fgets(buffer, sizeof(buffer), file);
            continue;
        }

        // Print the staff record to the temporary file
        fprintf(tempFile, "Id\t\t:%s \nNAME\t\t:%s \nAGE\t\t:%d \nGENDER\t\t:%s \nCONTACT NUMBER\t:%s \nADDRESS\t\t:%s\n\n\n",
                staff.id, staff.name, staff.age, staff.gender, staff.cNumber, staff.address);
        break;
    }

    fclose(file);
    fclose(tempFile); // Close the temporary file

    if (!found)
    {
        printf("Staff with ID %s not found.\n", idToDelete);
    }
    else
    {
        if (remove("staff.txt") == 0)
        {
            if (rename("temp.txt", "staff.txt") == 0)
            {
                printf("Staff information deleted successfully.\n");
            }
            else
            {
                printf("Error renaming the temporary file.\n");
            }
        }
        else
        {
            printf("Error deleting the original file.\n");
        }
    }
}






/*Staff page(Admin)*/
void staff_p()
{
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t***************************STAFF PAGE(ADMINE)***************************\n\n\n\n\n");
    printf("\t\t\t\t\t\t1.All Information of Staff\n");
    printf("\t\t\t\t\t\t2.Create form of Staff\n");
    printf("\t\t\t\t\t\t3.Back to Homepage\n\n\n\n");
    printf("\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");
    while(1)
    {
        int choice;
        printf("\t\t\tPlease your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            a_i_staff();               //All information of staff page
            break;
        case 2:
            c_staff_f();               //Create staff form page
            break;
        case 3:
            b_homepage();               //Back homepage(Admin)
            break;
        default:
        {
            system("cls");
            printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
            printf("\t\t\t**************************Staff PAGE(ADMINE)***************************\n\n\n\n");
            printf("\t\t\t\t\t\t1.All Information of Staff\n");
            printf("\t\t\t\t\t\t2.Create form of Staff\n");
            printf("\t\t\t\t\t\t3.Back to Homepage\n\n\n\n");
            printf("\t\t\t************************************************************************\n");
            printf("\t\t\t************************************************************************\n\n");
            printf("\t\t\tYour choice is WRONG.Please choice right option.\n");
        }

        }
    }
}




/*All
    Information
        Code
            Admin and Receptionist*/

/*Frist pagge*/
void frist_page()
{
    printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1.ADMINE\n");
    printf("\t\t\t\t\t\t\t2.RECEPTIONIST\n");
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t3.Exit");
    printf("\n\t\t\t************************************************************************\n");
    printf("\t\t\t************************************************************************\n\n");

    while(1)
    {
        int choise;
        printf("\t\t\tEnter your choise: ");
        scanf("%d",&choise);
        system("cls");  //clear screen

        fflush(stdin);
        switch(choise)
        {
            case 1:
                admine();
                break;

            case 2:
                receptionist();
                break;

            case 3:
                exit(1);

            default:
            {
                printf("\n\n\n\n\n\n\t\t\t************************************************************************\n");
                printf("\t\t\t************************************************************************\n\n\n\n");
                printf("\n\t\t\t\t\t\t\t1.ADMINE\n");
                printf("\t\t\t\t\t\t\t2.RECEPTIONIST\n");
                printf("\n\n\t\t\t\t\t\t\t\t\t\t\t3.Exit");
                printf("\n\n\t\t\t************************************************************************\n");
                printf("\t\t\t************************************************************************\n\n");
                printf("\t\t\tWrong Choise. Please Select the right choise.\n");
            }
        }
    }


}

int main()
{
    frist_page();

    return 0;
}


