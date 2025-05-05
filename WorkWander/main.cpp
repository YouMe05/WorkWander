#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <ctype.h>

using namespace std;

#include "NODE.h"
#include "applicant.h"
#include "post.h"
#include "user.h"
#include "job_seeker.h"
#include "company.h"
#include "LL.h"

int main()
{
    LL post_list;
    NODE *t;
    int order = 1;
    string id, co, location, title, workType, salary, description, requirement, time, resume;
    string username, name, about, skill, email, phone;
    fstream post;
    fstream appl;
    fstream file;

    User *user;
    int choice;
    string login;

    // Program Start
    system("CLS");
    cout << "\n\tWorkWander" << endl;
    cout << "-------------------------------------" << endl;
    cout << "  1. Job Seeker Login\n  2. Company Login\n  3. Register\n  0. Quit" << endl;
    choice = user->getInput(0, 3);

    switch (choice)
    {
    // Job seeker login
    case 1:
        login = user->login("jobSeeker/");
        if(login != "<failed>")
        {
            user = new JobSeeker(login);
            bool jobseeker_login = true;

            while (jobseeker_login)
            {
                post.open("post/post.txt", ios::in);
                while (!post.eof())
                {
                    getline(post, id);
                    if (id == "")
                        break;
                    getline(post, co);
                    getline(post, location);
                    getline(post, title);
                    getline(post, workType);
                    getline(post, salary);
                    getline(post, description);
                    getline(post, requirement);
                    getline(post, time);

                    t = new Post(order, id, co, location, title, workType, stoi(salary), description, requirement, time);
                    order++;
                    post_list.newPost(t);
                    appl.open("applicant/" + t->getID() + ".txt", ios::in);
                    if (appl)
                    {
                        while (!appl.eof())
                        {
                            getline(appl, username);
                            if (username == "")
                                break;
                            file.open("jobSeeker/" + username + "_profile.txt", ios::in);
                            getline(file, name);
                            getline(file, about);
                            getline(file, skill);
                            getline(file, email);
                            getline(file, phone);
                            getline(file, resume);
                            file.close();

                            t = new Applicant(name, about, skill, email, phone, resume);
                            post_list.newAppl(t);
                        }
                    }
                    appl.close();
                }
                post.close();
                post_list.applied(user->getUsername());

                int filter = 1;
                switch (choice = user->Menu())
                {
                case 1:
                    user->Profile();
                    break;

                // Seek Job
                case 2:
                    while (true)
                    {
                        system("CLS");
                        cout << "\n\tSeek Job" << endl;
                        cout << "----------------------------------------" << endl;
                        if (post_list.getSize() == 0 || post_list.getSize() == post_list.getNotShow())
                        {
                            cout << "\n           No posts found\n" << endl;
                            cout << "-------------------------------------" << endl;
                            cout << "Press Enter to Back to menu..." << endl;
                            cin.get();
                            cin.clear();
                            cin.ignore(10000, '\n');
                            break;
                        }
                        else
                        {
                            post_list.displaybyFilter(filter);
                        }

                        cout << "Menu 1. Apply job with post number\n     2. Job filter\n     0. Back to menu" << endl;
                        choice = user->getInput(0, 2);

                        // Apply Job
                        if (choice == 1)
                        {
                            post_list.apply(user);

                        }
                        // Filter
                        else if (choice == 2) {
                            system("CLS");
                            cout << "\n\tJob filter" << endl;
                            cout << "----------------------------------------" << endl;
                            cout << "  1. Order by newest\n  2. Salary high to low" << endl;
                            filter = user->getInput(1, 2);
                        }
                        // Back to menu
                        else break;
                    }
                    break;

                // Apllied Job
                case 3:
                    system("CLS");
                    post_list.displayApplied();
                    break;

                // Log out
                case 0:
                    delete user;
                    jobseeker_login = false;
                    break;
                }
                post_list.~LL();
            }
            main();
        }
        else
            main();
        break;

    // Company login
    case 2:
        login = user->login("company/");
        if(login != "<failed>")
        {
            user = new Company(login);
            bool company_login = true;

            while (company_login)
            {
                post.open("post/post.txt", ios::in);
                while (!post.eof())
                {
                    getline(post, id);
                    if (id == "")
                        break;
                    getline(post, co);
                    getline(post, location);
                    getline(post, title);
                    getline(post, workType);
                    getline(post, salary);
                    getline(post, description);
                    getline(post, requirement);
                    getline(post, time);

                    t = new Post(order, id, co, location, title, workType, stoi(salary), description, requirement, time);
                    order++;
                    post_list.newPost(t);
                    appl.open("applicant/" + t->getID() + ".txt", ios::in);
                    if (appl)
                    {
                        while (!appl.eof())
                        {
                            getline(appl, username);
                            if (username == "")
                                break;
                            file.open("jobSeeker/" + username + "_profile.txt", ios::in);
                            getline(file, name);
                            getline(file, about);
                            getline(file, skill);
                            getline(file, email);
                            getline(file, phone);
                            getline(file, resume);
                            file.close();

                            t = new Applicant(name, about, skill, email, phone, resume);
                            post_list.newAppl(t);
                        }
                    }
                    appl.close();
                }
                post.close();

                switch (choice = user->Menu())
                {
                case 1:
                    user->Profile();
                    break;

                case 2:
                    user->post();
                    break;
                case 3:
                    post_list.displayMyPost(user);
                    break;

                case 0:
                    delete user;
                    company_login = false;
                    break;
                }
                post_list.~LL();
            }
            main();
        }
        else
            main();
        break;

    // Register
    case 3:
        user->RegisPage();
        main();
        break;

    // Quit
    case 0:
        return 0;
        exit(1);
    }

    return 0;
}
