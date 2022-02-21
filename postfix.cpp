#include<iostream>
#include<stack>
#include<math.h>
#include <string>
#include <stdlib.h>
using namespace std;

double calculate_Postfix(string  post_exp) {

    stack <double> stack;
    int len = post_exp.length();
    long double m[100] = {};
    int indeksi = 0;
    double b = 0;

    //aletaan looppaan stringiä läpi
    for (int i = 0; i < len; i++) {

        if (post_exp[i] >= '0' && post_exp[i] <= '9' || post_exp[i] =='.') {
            if (post_exp[i] == '.') {
                double luku1 = ( post_exp[i - 1]-'0');
                double luku2 = (post_exp[i + 1]-'0');
                double luku3 = luku2 / 10;
                double luku4 = luku1 + luku3;
                stack.pop();
                stack.push(luku4);
                i++;
            }
            else{
            stack.push(post_exp[i] - '0');
            indeksi++;
            }
        }

        // jos onkin operaattori (ei luku väliltä 0-9) niin toteutetaan operaatio
        else {
            int numero = len - indeksi;

            // otetaan stackista kaikki numerot m arrayhin
            int f = 0;
            while (!stack.empty()) {
                m[f] = { stack.top() };
                stack.pop();
                f++;
            }
            f = 0;
            int laskin = indeksi - 1;

            switch (post_exp[i]) {

            case 'x': //swap 
                for (f = 0; f < indeksi; f++) {
                    stack.push(m[f]);
                    laskin++;
                }
                f = 0;
                break;

            case 's': // sum
                for (f = 0; f < len - numero; f++) {
                    b = b + m[f];
                }
                f = 0;
                stack.push(b);
                break;

            case '+':
                for (f = 0; f < len - numero; f++) {
                    b = b + m[f];
                }
                f = 0;
                stack.push(b);
                break;

            case '-':  //minus
                for (f = 0; f < indeksi; f++) {
                    stack.push(m[f]);
                    laskin++;
                };
                f = 0;
                while (!stack.empty()) {
                    m[f] = { stack.top() };
                    stack.pop();
                    f++;
                };
                f = 0;
                b = m[0];
                for (int y = 1; y < indeksi; y++) {                   
                    b = b - (m[y]);
                };
                stack.push(b);

                f = 0;
                break;
            
            case'a': //average
                for (f = 0; f < len - numero; f++) {
                    b = b + m[f];
                };
                b = b / indeksi;
                f = 0;
                stack.push(b);
                break;

            case'*': //multiplication
                b = m[0];
                for (f = 1; f < len - numero; f++) {

                    b = b * m[f];
                };
                f = 0;
                stack.push(b);
                break;

            case '/':  //divide
                for (f = 0; f < indeksi; f++) {
                    stack.push(m[f]);
                    laskin++;
                };
                f = 0;
                while (!stack.empty()) {
                    m[f] = { stack.top() };
                    stack.pop();
                    f++;
                };
                f = 0;
                b = m[0];
                for (int y = 1; y < indeksi; y++) { //len-numero                   
                    b = b / (m[y]);
                };
                stack.push(b);
                f = 0;
                break;

            case '%':  //remainder
                b = fmod(m[0], m[1]);
                stack.push(b);
                break;

            case '^':  //potency
                b = pow(m[0], m[1]);
                stack.push(b);
                break;

            case 'v':  //square
                b = sqrt(m[0]);
                stack.push(b); 
                break;
        }
            //puhdistetaan m-taulukko, jotta vanhat numerot eivät jää kummittelemaan
            for (int x = 0; x < indeksi+1; x++) {
                m[x] = 0;
            }
            
            indeksi = 1;    
        }

    }
    return stack.top();
}

int main(int argc, char* argv[]) {

    string postfix_expression = argv[1];
    //string postfix_expression = "13+7.5-";    testi
    //string postfix_expression = "123a";       testi
    //string postfix_expression = "12x-";       testi
    //string postfix_expression = "123s";       testi
    //string postfix_expression = "42^";        testi
    //string postfix_expression = "p";          testi
    if (postfix_expression == "p") {
        cout << "Syota numerot ja taman jalkeen operaattori esim. '123+4-'" << endl;
        cout << "Operaattorit ovat:\n + = pluslasku\n s = pluslasku\n - = miinuslasku\n x = vaihtaa kaksi ylinta lukua\n a = keskiarvo \n * = kertolasku\n / = jakolasku\n % = jakojaannos \n ^ = potenssi\n v = neliojuuri\n Aja ohjelma uudelleen" << endl;
    }
    else {
        cout << "The answer after calculating the postfix expression is : ";
        cout << calculate_Postfix(postfix_expression) << endl;
    }
    return 0;
}