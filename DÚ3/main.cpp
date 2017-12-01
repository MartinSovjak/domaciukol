#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#define EASTER_OK                0
#define EASTER_INVALID_FILENAME  1
#define EASTER_INVALID_YEARS     2
#define EASTER_IO_ERROR          3


#endif /* __PROGTEST__ */
int rozsah(int,int,const char*);
int gregorian(int, const char*);
int easterReport (const char *,const char *);
string stringOkay(string);
int notColidingYears(string);
int fileNameOkay(string);
int startFile(const char *);
int endFile(const char *);



#ifndef __PROGTEST__
int main ( int argc, char * argv[] ){
/*
    char years[] = "2002";
    char outFileName[] = "out.html";


    cout << easterReport(years,outFileName);
*/
/* tests */
    return 0;

}
#endif /* __PROGTEST__ */

int easterReport (const char * years,const char * outFileName )
{
    string fileName = outFileName;
    string yearsString = years;

    int fileOk = fileNameOkay(fileName);
    if (fileOk != 0)
        return (EASTER_INVALID_FILENAME);

    yearsString = stringOkay(yearsString);


    int colide = notColidingYears(yearsString);
    if (colide != 0)
        return (EASTER_INVALID_YEARS);

    int yearsStringLength = yearsString.length();

    if(startFile(outFileName)!= 0)
        return (EASTER_IO_ERROR);

    if (yearsStringLength > 4){

        for (int gettingNumbers = 0; gettingNumbers < yearsStringLength; gettingNumbers+=5){
            int number = ((yearsString.at(gettingNumbers)-'0')*1000)+((yearsString.at(gettingNumbers+1)-'0')*100)+((yearsString.at(gettingNumbers+2)-'0')*10)+(yearsString.at(gettingNumbers+3)-'0');
            int number2;

            if (gettingNumbers + 4 < yearsStringLength){

                if (yearsString.at(gettingNumbers+4) == ','){

                        gregorian(number,outFileName);

                }
                if (yearsString.at(gettingNumbers+4) == '-'){

                        number2 = ((yearsString.at(gettingNumbers+5)-'0')*1000)+((yearsString.at(gettingNumbers+6)-'0')*100)+((yearsString.at(gettingNumbers+7)-'0')*10)+(yearsString.at(gettingNumbers+8)-'0');
                        rozsah(number,number2,outFileName);
                        gettingNumbers+=5;
                }


            }
            if (gettingNumbers + 4 >= yearsStringLength && yearsString.at(gettingNumbers-1) != '-'){
                gregorian (number,outFileName);
            }

        }
    }
    if (yearsStringLength == 4){
        int number = ((yearsString.at(0)-'0')*1000)+((yearsString.at(1)-'0')*100)+((yearsString.at(2)-'0')*10)+(yearsString.at(3)-'0');
        gregorian(number,outFileName);
    }

    if(endFile(outFileName)!= 0)
        return (EASTER_IO_ERROR);
    return(EASTER_OK);
}

int fileNameOkay(string fileName){

    int fileNameLength = fileName.length()-1;
            if (fileNameLength < 6)
                return (EASTER_INVALID_FILENAME);

    for (int i = 0; i <= fileNameLength; i++){
            char a = fileName.at(i);

        if (((a < '.') || (a > '9' && a < 'A') || (a > 'Z' && a < 'a') || (a > 'z')) && (a != 92)){
               return (EASTER_INVALID_FILENAME);
        }

    }
    int j = fileNameLength;

    if ((fileName.at(j) != 'l') || (fileName.at(j-1) != 'm') || (fileName.at(j-2) != 't') || (fileName.at(j-3) != 'h') || (fileName.at(j-4) != '.'))
        return (EASTER_INVALID_FILENAME);

    return(EASTER_OK);
}

string stringOkay(string ahoj){

    string str = ahoj;
    int length = str.length();
    char c;
    for (int i = length-1; i >= 0; --i) {
        c = str[i];
        if(isspace(c))
            str.erase(i, 1);

    }

    return (str);
}

int notColidingYears(string str){

    int length = str.length();
    int number1, number2;
    if (length >= 5 && (length-4)%5 != 0)
        return (EASTER_INVALID_YEARS);

    if (length > 5){
        for (int i = 4; i < length; i++){

        if (str.at(i) == '-') {

                for (int j = 1; j < 5; j++){
                    if (str.at(i-j) < '0' || str.at(i-j) > '9')
                        return (EASTER_INVALID_YEARS);
                    if (str.at(i+j) < '0' || str.at(i+j) > '9')
                        return (EASTER_INVALID_YEARS);
                }

            number1 = ((str.at(i-4)-'0')*1000)+((str.at(i-3)-'0')*100)+((str.at(i-2)-'0')*10)+(str.at(i-1)-'0');
            number2 = ((str.at(i+1)-'0')*1000)+((str.at(i+2)-'0')*100)+((str.at(i+3)-'0')*10)+(str.at(i+4)-'0');

            if (number1 > number2)
                return (EASTER_INVALID_YEARS);
        }
    }
        for (int i = 0; i < length; i+=5){
            number1 = ((str.at(i)-'0')*1000)+((str.at(i+1)-'0')*100)+((str.at(i+2)-'0')*10)+(str.at(i+3)-'0');

            if (number1 < 1583 || number1 >= 2200)
                return (EASTER_INVALID_YEARS);
        }
    }

    if (length == 4) {
        number1 = ((str.at(0)-'0')*1000)+((str.at(1)-'0')*100)+((str.at(2)-'0')*10)+(str.at(3)-'0');

            if (number1 < 1582 || number1 > 2200)
                return (EASTER_INVALID_YEARS);
    }
    if (length < 4)
        return (EASTER_INVALID_YEARS);

    return (EASTER_OK);
}

int startFile (const char * fileName){

    ofstream myFile;
    myFile.exceptions ( ofstream::failbit | ofstream::badbit );
        try {
            myFile.open (fileName, std::ofstream::out | std::ofstream::app);
            myFile << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">" << endl; //starting html
            myFile << "<html>" << endl << "<head>" << endl << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" << endl << "<title>C++</title>" << endl << "</head>" << endl;
            myFile << "<body>" << endl;
            myFile << "<table width=\"300\">" << endl << "<tr><th width=\"99\">den</th><th width=\"99\">mesic</th><th width=\"99\">rok</th></tr>" << endl;
        }
        catch (const ofstream::failure& e){
            return (EASTER_IO_ERROR);
        }
    myFile.close();

    return(EASTER_OK);
}
int gregorian(int date, const char* fileName){

    int Y = date;
    int A = Y%19;
    int B = Y/100;
    int C = Y%100;
    int D = B/4;
    int E = B%4;
    int F = (B+8)/25;
    int G = (B-F+1)/3;
    int H = ((19*A)+B-D-G+15)%30;
    int I = C/4;
    int K = C%4;
    int L = (32+(2*E)+(2*I)-H-K)%7;
    int M = (A+(11*H)+(22*L))/451;
    int N = (H+L-(7*M)+114)/31;
    int P = (H+L-(7*M)+114)%31;
    int easterDay = (P+1);

    string easterMonth;
    if (N == 3)
        easterMonth = "brezen";
    if (N == 4)
        easterMonth = "duben";
    int easterYear = Y;


    ofstream myFile;

    myFile.exceptions ( ofstream::failbit | ofstream::badbit );
    try {
        myFile.open (fileName, std::ofstream::out | std::ofstream::app);

        myFile << string("<tr><td>");//+easterDay+string("</td><td>")+string(easterMonth)+string("</td><td>")+easterYear+string("</td></tr>");
        myFile << easterDay;
        myFile << string("</td><td>");
        myFile << easterMonth;
        myFile << string("</td><td>");
        myFile << easterYear;
        myFile << string("</td></tr>") << endl;
    }
    catch (const ofstream::failure& e) {
        return(EASTER_IO_ERROR);
    }

    myFile.close();


    return(EASTER_OK);
}
int rozsah(int number,int number2, const char* fileName){

    for (int i = number; i <= number2; i++){
        gregorian(i,fileName);
    }
    return (0);
}

int endFile (const char* fileName){
    ofstream myFile;
    myFile.exceptions ( ofstream::failbit | ofstream::badbit );
     try {
        myFile.open (fileName, std::ofstream::out | std::ofstream::app);

        myFile << "</table>" << endl;
        myFile << "</body>" << endl;
        myFile << "</html>" << endl;
     }
     catch(const ofstream::failure& e){
        return(EASTER_IO_ERROR);
     }
     myFile.close();
     return (EASTER_OK);
}
