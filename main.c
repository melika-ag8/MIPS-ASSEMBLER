#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define R_type 0
#define I_type 1
#define J_type 2

const char *instruction[] = {"add", "sub", "slt", "or", "nand", "addi", "ori", "slti", "lui", "lw", "sw", "beq", "jalr","j", "halt"};

struct symbolpSymTab
{
    int value;
    char * symbol;
};

struct instruction
{
    size_t type; //0-1-2
    char * mnemonic; //name of instruction
    int decimal; //decimal
    char instruction[10]; //hex
    int rs ;
    int rt;
    int rd;
    int imm;
    int pc; //instruction-count pc+1
};

// count lables
int findsymtab_len(FILE* inputfile)
{
    int count = 0;
    size_t linesize;
    char * line ;
    line = (char*)malloc(72);

    while (getline(&line, &linesize, inputfile) != -1)
    {
        if (!(line[0] == ' ' || line[0] == '\t'))
            count++;
    }
    rewind(inputfile);
    free(line);
    return count;
}

// creat the table of lables
int fillsymTab( struct symbolpSymTab* symt, FILE* inputfile)
{
    int noline = 0, i = 0;
    size_t linesize;
    char* line ;
    line = (char*)malloc(72);
    char* token;

    while (getline(&line, &linesize, inputfile) != -1)
    {
        if (!(line[0] == ' ' || line[0] == '\t'))
        {
            token = strtok(line, " \t ");
            strcpy(symt[i].symbol, token);
            symt[i].value = noline;
            i++;
        }
        noline++;
    }
    rewind(inputfile);
    free(line);
    return noline ;
}

char * decToBinary(int n)
{
    char * bin = (char*)malloc(5 * sizeof(char));;
    int j = 0 ;

    for (int i = 3; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
        {
            bin[j] = '1' ;
        }

        else
        {
            bin[j] = '0' ;
        }
        j++ ;
    }

    return bin ;
}

char * decToBinaryimmij(int n)
{
    char * bin = (char*)malloc(17 * sizeof(char));
    int j = 0 ;

    for (int i = 15; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
        {
            bin[j] = '1' ;
        }

        else
        {
            bin[j] = '0' ;
        }
        j++ ;
    }
    bin[j] = '\0' ;

    return bin ;
}

int binaryTodec(char * code,int len)
{
    int dec[32];
    int output = 0;
    int power = 1;

    for (int i = 0 ; i < 32 ; i++)
    {
        dec[i] = code[i]-'0' ;
    }
    for (int i = 0; i < len; i++)
    {
        output += dec[(len - 1) - i] * power;
        power *= 2;
    }
    return output;
}

/*void reverse(char* str)
{
    if (!*str)
    {
        return;
    }

    char* begin = str;
    char* end = begin + strlen(str) - 1;

    while (begin < end)
    {
        char c = * begin;
        *begin = *end;
        *end = c;

        begin++;
        end--;
    }
}*/

char * dectohex(int n)
{
    /*long quotient, remainder;
    int i, j = 0;
    char * hexan = (char*)malloc(100 * sizeof(char));

    quotient = n;

    while (quotient != 0)
    {
        remainder = quotient % 16;
        if (remainder < 10)
            hexan[j++] = 48 + remainder;
        else
            hexan[j++] = 55 + remainder;
        quotient = quotient / 16;
    }

    reverse(hexan);
    return hexan ;*/

    char * hexq = (char*)malloc(100 * sizeof(char));
    sprintf(hexq,"%#X",n); // convert decimal to hexadecimal

    return hexq ;
}

void toMachineCode(struct instruction *current_ins,FILE* machp )
{
    char code[32] = "0000" ;

    if(strcmp(current_ins->mnemonic,"add") == 0)
    {
        strcat(code, "0000");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinary(current_ins->rd));
        strcat(code,"000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction);

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"sub") == 0)
    {
        strcat(code, "0001");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinary(current_ins->rd));
        strcat(code,"000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"slt") == 0)
    {
        strcat(code, "0010");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinary(current_ins->rd));
        strcat(code,"000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"or") == 0)
    {
        strcat(code, "0011");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinary(current_ins->rd));
        strcat(code,"000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"nand") == 0)
    {
        strcat(code, "0100");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinary(current_ins->rd));
        strcat(code,"000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"addi") == 0)
    {
        strcat(code, "0101");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"ori") == 0)
    {
        strcat(code, "0111");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"slti") == 0)
    {
        strcat(code, "0110");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"lui") == 0)
    {
        strcat(code, "1000");
        strcat(code, "0000");
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"lw") == 0)
    {
        strcat(code, "1001");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"sw") == 0)
    {
        strcat(code, "1010");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"beq") == 0)
    {
        strcat(code, "1011");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, decToBinaryimmij(current_ins->imm));

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if(strcmp(current_ins->mnemonic,"jalr") == 0)
    {
        strcat(code, "1100");
        strcat(code, decToBinary(current_ins->rs));
        strcat(code, decToBinary(current_ins->rt));
        strcat(code, "0000000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if (strcmp(current_ins->mnemonic,"j") == 0)
    {
        strcat(code, "1101");
        strcat(code, "00000000");
        strcat(code, decToBinaryimmij(current_ins->imm)) ;

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    else if (strcmp(current_ins->mnemonic,"halt") == 0)
    {
        strcat(code,"1110");
        strcat(code,"000000000000000000000000");

        printf("%s \t %s \n", "bin", code);

        current_ins->decimal = binaryTodec(code,32) ;
        printf("%s \t %d \n", "dec", current_ins->decimal) ;

        int s = current_ins->decimal ;
        strcpy(current_ins->instruction, dectohex(s));
        printf("%s \t %s \n", "hex", current_ins->instruction  );

        fprintf(machp,"%d \n",s);
    }
    printf("\n");
}

void print_symbol(struct symbolpSymTab* pSymTab, int symtab_len)
{
    for (int i = 0; i < symtab_len; i++)
    {
        printf("%d \t %s\n", pSymTab[i].value, pSymTab[i].symbol);
    }
}

int main(int argc, char** argv)
{
    char * token ;
    char * line ;
    line = (char*)malloc(72);
    size_t linesize ;

    int ins_count = 0;

    struct instruction *current_ins;
    current_ins = (struct instruction*)malloc(sizeof(struct instruction));

    FILE * assp, * machp, * fopen();

    if (argc < 3)
    {
        printf("***** Please run this program as follows:\n");
        printf("***** %s assprog.as machprog.m\n", argv[0]);
        printf("***** where assprog.as is your assembly program\n");
        printf("***** and machprog.m will be your machine code.\n");
        exit(1);
    }
    if ((assp = fopen(argv[1], "r")) == NULL)
    {
        printf("%s cannot be openned\n", argv[1]);
        exit(1);
    }
    if ((machp = fopen(argv[2], "w+")) == NULL)
    {
        printf("%s cannot be openned-\n", argv[2]);
        exit(1);
    }

// count lables
    int symtab_len = findsymtab_len(assp);

    struct symbolpSymTab* pSymTab ;
    pSymTab = (struct symbolpSymTab*)malloc(symtab_len * sizeof(struct symbolpSymTab));

    for (int i = 0; i < symtab_len; i++)
    {
        pSymTab[i].symbol = (char *) malloc(7);
    }
// create the table of lables
    int noinstruction = fillsymTab(pSymTab, assp);

    printf("\npSymTab is as below\n");
    printf("\n");

    print_symbol( pSymTab,symtab_len);

    /*for(int i=0; i<symtab_len; i++)
    {
        printf("%d \t %s \n", pSymTab[i].value , pSymTab[i].symbol);
    }*/
    printf("\n");

// duplicate lable
    for(int i=0; i<symtab_len; i++ )
    {
        for(int j=i+1; j<symtab_len-1; j++)
        {
            if(strcmp(pSymTab[i].symbol,pSymTab[j].symbol) == 0)
            {
                printf("%s \t %s \n", "error: duplicate label found->",pSymTab[i].symbol);
                exit(1);
            }
        }
    }

    printf("the instructions are as below\n");
    printf("\n");
////////////////////////////////////////////////////////////////////////////////////////////
    while(getline(&line,&linesize,assp) != -1)
    {
        int check = 0 ;
        current_ins->pc =ins_count;
        ins_count++;
        token=strtok(line,"\t,\n");

        // check for labels
        for(int i=0; i<symtab_len; i++)
        {
            if(strcmp(pSymTab[i].symbol,token) == 0)
            {
                token=strtok(NULL,"\t,\n");
            }
        }

        //instruction:
        strcpy(current_ins->mnemonic,token);
        current_ins->type=-1;

        // check .fill
        if(current_ins->mnemonic[0] == '.' && current_ins->mnemonic[1] == 'f')
        {
            token=strtok(NULL,"\t,\n");
            if ((48 <= token[0] && token[0] <= 57 ) ||  token[0] == 45)
            {
                current_ins->decimal=atoi(token);

                if (current_ins->decimal > 65536)
                {
                    printf("%s \t %d \n", "error: offset is too big->", current_ins->decimal);
                    exit(1);
                }
                else
                {
                    printf("%s \t %d \n", ".fill", current_ins->decimal);
                    printf("%s \t %d \n", "dec", current_ins->decimal) ;

                    strcpy (current_ins->instruction, dectohex(atoi(token)));
                    printf("%s \t %s \n", "hex", current_ins->instruction );

                    fprintf(machp,"%d \n", current_ins->decimal);
                }
            }
            else
            {
                for(int i=0; i<symtab_len; i++)
                {
                    if(strcmp(pSymTab[i].symbol,token) == 0)
                    {
                        current_ins->decimal = pSymTab[i].value ;
                        check = 1 ;

                        printf("%s \t %d \n", ".fill", current_ins->decimal);
                        printf("%s \t %d \n", "dec", current_ins->decimal) ;

                        strcpy(current_ins->instruction, dectohex(pSymTab[i].value));
                        printf("%s \t %s \n", "hex", current_ins->instruction );

                        fprintf(machp,"%d \n", current_ins->decimal);

                    }
                }
                if (check == 0)
                {
                    printf("%s \t %s \n", "error: label not defined->",token);
                    exit(1);
                }
            }
            printf("\n");
        }
        // all R type
        else if(strcmp(current_ins->mnemonic,instruction[0]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[1]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[2]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[3]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[4]) == 0)
        {
            current_ins->type = 0 ; //R

            token = strtok(NULL, "\t,\n");
            current_ins->rd =atoi(token);
            token = strtok(NULL, "\t,\n");
            current_ins->rs =atoi(token);
            token = strtok(NULL, "\t,\n");
            current_ins->rt =atoi(token);

            printf("%s \t %s \t", "type r",current_ins->mnemonic);
            printf("%d \t %d \t %d \n",current_ins->rd, current_ins->rs, current_ins->rt);
            toMachineCode(current_ins,machp);
        }
        // I type
        else if(strcmp(current_ins->mnemonic,instruction[5]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[6]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[7]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[9]) == 0 ||
                strcmp(current_ins->mnemonic,instruction[10]) == 0)
        {
            current_ins->type =1 ; //I

            token = strtok(NULL, "\t,\n");
            current_ins->rt =atoi(token);
            token = strtok(NULL, "\t,\n");
            current_ins->rs =atoi(token);
            token = strtok(NULL, "\t,\n");
            if(isdigit(token[0]))
            {
                current_ins->imm =atoi(token);

                printf("%s \t %s \t", "type i",current_ins->mnemonic);
                printf("%d \t %d \t %s \n",current_ins->rt,current_ins->rs, token);
            }

            else
            {
                for(int i=0; i<symtab_len; i++)
                {
                    if(strcmp(pSymTab[i].symbol,token) == 0)
                    {

                        current_ins->imm = pSymTab[i].value ;
                        check = 1 ;

                        printf("%s \t %s \t", "type i",current_ins->mnemonic);
                        printf("%d \t %d \t %s \n",current_ins->rt,current_ins->rs, token );
                        printf("%s \t %s \t", "mean ",current_ins->mnemonic);
                        printf("%d \t %d \t %d \n", current_ins->rt,current_ins->rs,current_ins->imm );
                    }
                }
                if (check==0)
                {
                    printf("%s \t %s \n", "error: label not defined->",token);
                    exit(1);
                }
            }
            toMachineCode(current_ins,machp);
        }
        // I type lui
        else if (strcmp(current_ins->mnemonic,instruction[8]) == 0)
        {
            current_ins->type = 1;

            token = strtok(NULL, "\t,\n");
            current_ins->rt =atoi(token);
            token = strtok(NULL, "\t,\n");
            current_ins->imm =atoi(token);

            printf("%s \t %s \t ", "type i",current_ins->mnemonic);
            printf("%d \t %d \n",current_ins->rt, current_ins->imm );
            toMachineCode(current_ins,machp);
        }
        // I type beq
        else if ((strcmp(current_ins->mnemonic,instruction[11]) == 0))
        {
            current_ins->type = 1;

            token = strtok(NULL, "\t,\n");
            current_ins->rs =atoi(token);
            token = strtok(NULL, "\t,\n");
            current_ins->rt =atoi(token);
            token = strtok(NULL, "\t,\n");
            if(isdigit(token[0]))
            {
                current_ins->imm =atoi(token) -1 - current_ins->pc;

                printf("%s \t %s \t ", "type i",current_ins->mnemonic);
                printf("%d \t %d \t %s \n",current_ins->rs, current_ins->rt,token );
            }

            else
            {
                for(int i=0; i<symtab_len; i++)
                {
                    if(strcmp(pSymTab[i].symbol,token) == 0)
                    {
                        current_ins->imm = pSymTab[i].value -1 - current_ins->pc ;
                        check = 1 ;

                        printf("%s \t %s \t ", "type i",current_ins->mnemonic);
                        printf("%d \t %d \t %s \n",current_ins->rs, current_ins->rt,token  );
                        printf("%s \t %s \t", "mean ",current_ins->mnemonic);
                        printf("%d \t %d \t %d \n", current_ins->rt,current_ins->rs,current_ins->imm );
                    }
                }
                if (check ==0)
                {
                    printf("%s \t %s \n", "error: label not defined->",token);
                    exit(1);
                }
            }

            toMachineCode(current_ins,machp);
        }
        // I type jalr
        else if (strcmp(current_ins->mnemonic,instruction[12]) == 0 )
        {
            current_ins->type = 1;


            printf("%s \t %s \t", "type i",current_ins->mnemonic);

            token = strtok(NULL, "\t,\n");
            current_ins->rt =atoi(token);
            token = strtok(NULL, "\t,\n");
            current_ins->rs =atoi(token);

            printf("%d \t %d \n",current_ins->rt, current_ins->rs);
            toMachineCode(current_ins,machp);
        }
        // J type j
        else if(strcmp(current_ins->mnemonic,instruction[13]) == 0 )
        {
            current_ins->type= 2 ;

            token = strtok(NULL, "\t,\n");
            if(isdigit(token[0]))
            {
                current_ins->imm =atoi(token);

                printf("%s \t %s \t", "type j",current_ins->mnemonic);
                printf("%s \n", token /*current_ins->imm*/);
            }
            else
            {
                for(int i=0; i<symtab_len; i++)
                {
                    if(strcmp(pSymTab[i].symbol,token) == 0)
                    {
                        current_ins->imm = pSymTab[i].value ;
                        check = 1 ;

                        printf("%s \t %s \t", "type j",current_ins->mnemonic);
                        printf("%s \n", token);
                        printf("%s \t %s \t", "mean",current_ins->mnemonic);
                        printf("%d \n",current_ins->imm);
                    }
                }
                if (check ==0)
                {
                    printf("%s \t %s \n", "error: label not defined->",token);
                    exit(1);
                }
            }
            toMachineCode(current_ins,machp);
        }
        // J type halt
        else if (strcmp(current_ins->mnemonic,instruction[14]) == 0)
        {
            current_ins->type= 2 ;

            printf("%s \t %s \n", "j ",current_ins->mnemonic);
            toMachineCode(current_ins,machp);

            //exit(1) ;
        }
        else
        {
            printf("%s %s \n", "error: opcode not defined->", current_ins->mnemonic);
            printf("\n");
            exit(1);
        }
    }

    fclose(assp);
    fclose(machp);
    exit(0) ;
}
