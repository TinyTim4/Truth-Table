#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#include<math.h> 


struct var {
    char name[40];
    int order;
    struct var* next;
    int *values;
};

void pushVar(struct var** top_ref, char* new_data, int num, int num2) {
    struct var* new_var = (struct var*)malloc(sizeof(struct var));
	struct var* ptr = *top_ref;
    if(ptr == NULL) {
		strcpy(new_var->name, new_data);
        new_var->order = num;
		new_var->next = (*top_ref);
		(*top_ref) = new_var;
	}
    else {
        while(ptr) {
            if(ptr->next == NULL) {
				strcpy(new_var->name, new_data);
                new_var->order = num;
				ptr->next = new_var;
				new_var->next = NULL;
				break;
			}
            ptr = ptr->next;
        }
    }
    if(num < num2+2) {
        int rows = (int)pow(2,num2);
        int *x = (int *)malloc((rows) * sizeof(int));
        int change = (int)pow(2,(num2-1)-(num-2));
        int val = 1;
        for(int j = 0; j < rows; j++) {
            if(j % change == 0) {
                if(val == 0) {
                    val = 1;
                }
                else {
                    val = 0;
                }
            }
            x[j] = val;
        }
        new_var->values = x;
    }
}

void pop(struct var** top_ref)
{
	struct var* top;
	top = *top_ref;
	*top_ref = top->next;
    free(top->values);
	free(top);
}

void pushArr(struct var* top_ref, int order, int* arr) {
    struct var* ptr = top_ref;
    while(ptr) {
        if(ptr->order == order) {
            ptr->values = arr;
            break;
        }
        ptr = ptr->next;
    }
}

int searchOrder(struct var* top_ref, char* name) {
    struct var *ptr = top_ref;
    char target[40];
    int num = -1;
    strcpy(target, name);
    while(ptr) {
        if(strcmp(ptr->name, target) == 0) {
            num = ptr->order;
            break;
        }
        ptr = ptr->next;
    }
    return num;
}

int* searchArr(struct var* top_ref, int num, int size) {
    struct var *ptr = top_ref;
    int *arr = (int *)malloc((size) * sizeof(int));
    while(ptr) {
        if(ptr->order == num) {
            for(int i = 0; i<size; i++) {
                arr[i] = ptr->values[i];
            }
        }
        ptr = ptr->next;
    }
    return arr;
}

int multiplex(int* input, int* select, int x) {
    int total = (int)pow(2,x);
    int**si = (int**)malloc((x)*sizeof(int*));
    for(int k = 0; k < x; k++) {
        si[k] = (int*)malloc((total) * sizeof(int));
    }
    int change = (int)pow(2, (x-1));
    for(int k = 0; k < x; k++) {
        int val = 1;
        for(int j = 0; j < total; j++) {
            if(j % change == 0) {
                if(val == 0) {
                    val = 1;
                }   
                else {
                    val = 0;
                }
            }
            si[k][j] = val;
        }
        change = change/2;
    }
    int det=0;
    int ans;
    for(int k = 0; k < total;k++) {
        for(int i = 0; i < x; i++) {
            if(select[i] != si[i][k]) {
                det = 0;
                break;
            }
            else {
                det = 1;
            }
        }
        if (det == 1) {
            ans = input[k];
            break;
        }
    }
    for(int k = 0; k < x; k++) {
        free(si[k]);
    }
    free(si);
    return ans;
    
    
}

int and(int i1, int i2) {
    int r = i1*i2;
    return r;
}

int nand(int i1, int i2) {
    int r = i1*i2;
    if(r == 0) {
        r = 1;
    }
    else {
        r = 0;
    }
    return r;
}

int or(int i1, int i2) {
    int r = i1+i2;
    if(r == 2) {
        r = 1;
    }
    return r;
}

int nor(int i1, int i2) {
    int r = i1+i2;
    if(r == 2) {
        r = 1;
    }
    if(r==1) {
        r = 0;
    }
    else {
        r = 1;
    }
    return r;
}

int decoder(int* comp, int x, int index) {
    int total = (int)pow(2,x);
    int**si = (int**)malloc((total)*sizeof(int*));
    for(int k = 0; k < total; k++) {
        si[k] = (int*)malloc((x) * sizeof(int));
    }
    int change = (int)pow(2, (x-1));
    for(int k = 0; k < x; k++) {
        int val = 1;
        for(int j = 0; j < total; j++) {
            if(j % change == 0) {
                if(val == 0) {
                    val = 1;
                }   
                else {
                    val = 0;
                }
            }
            si[j][k] = val;
        }     
        change = change/2;
    }
    int**dec = (int**)malloc((total)*sizeof(int*));
    for(int k = 0; k < total; k++) {
        dec[k] = (int*)malloc((total) * sizeof(int));
    }
    for(int i = 0; i < total; i++) {
        for(int j = 0; j < total; j++) {
            if(j == i) {
                dec[i][j] = 1;
            }
            else {
                dec[i][j] = 0;
            }
        }
    }
    int det=0;
    int ans;
    for(int k = 0; k < total;k++) {
        for(int i = 0; i < x; i++) {
            if(comp[i] != si[k][i]) {
                det = 0;
                break;
            }
            else {
                det = 1;
            }
        }
        if (det == 1) {
            ans = dec[k][index];
            break;
        }
    }
    for(int k = 0; k < total; k++) {
        free(si[k]);
    }
    for(int k = 0; k < total; k++) {
        free(dec[k]);
    }
    free(dec);
    free(si);
    return ans;
}
int not(int i1) {
    int r;
    if(i1 == 0) {
        r = 1;
    }
    else {
        r = 0;
    }
    return r;
}
int xor(int i1, int i2) {
    int r = i1+i2;
    if(r == 2) {
        r = 0;
    }
    return r;
}
int main(int argc, char *argv[]) {
    struct var* variables = NULL;
    FILE *circ;
    circ = fopen(argv[1], "r");
    char word[40];
    int inputs = 0;
    fscanf(circ, "%s", word);
    fscanf(circ, "%d", &inputs);
    for(int k = 0; k < inputs; k++) {
        fscanf(circ, "%s", word);
        pushVar(&variables, word, k+2, inputs);
    }
    fscanf(circ, "%s", word);
    int outputs = 0;
    fscanf(circ, "%d", &outputs);
     for(int k = 0; k < outputs; k++) {
        fscanf(circ, "%s", word);
        pushVar(&variables, word, k+2+inputs, inputs);
    }
    int size = (int)pow(2,inputs);
    int**inputArr = (int**)malloc((inputs)*sizeof(int*));
    for (int i = 0; i < inputs; i++) {
        inputArr[i] = searchArr(variables, i+2, size);
    }
    int count = 0;
    char** file = (char**)malloc((sizeof(char*)));
    int r = 0;
    while(fscanf(circ, "%s", word) != EOF) {
        file = realloc(file, (r+1)*sizeof(char*));
        for(int i = r; i < r+1; i++) {
            file[i] = (char*)malloc((16)*sizeof(char));
        }
        strcpy(file[r], word);
        r++;
    }
    int tot = r;
    r = 0;
    while(r < tot) {
        if(strcmp(file[r], "AND") == 0) {
            r++;
            strcpy(word, file[r]);
            int var1 = searchOrder(variables, word);
            if(var1-2 > inputs) {
                var1 = var1 - outputs;
            }
            else if(var1 < 0) {
                char *ptr;
                var1 = (int)strtol(word, &ptr, 10);
            }
            r++;
            strcpy(word, file[r]);
            int var2 = searchOrder(variables, word);
            if(var2-2 > inputs) {
                var2 = var2 - outputs;
            }
            else if(var2 < 0) {
                char *ptr2;
                var2 = (int)strtol(word, &ptr2, 10);
            }
            r++;
            strcpy(word, file[r]); 
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int var3 = searchOrder(variables, word);
            int *temp3 = (int*)malloc((size) * sizeof(int));
            for(int i = 0; i < size; i ++) {
                int x;
                int y;
                if(var1 < 2) {
                    x = var1;
                }
                else {
                    x = inputArr[var1-2][i];
                }
                if(var2 < 2) {
                    y = var2;
                } 
                else {
                    y = inputArr[var2-2][i];
                }
                temp3[i] = and(x, y);
            }
            pushArr(variables, var3, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var3, size);
        }
        else if(strcmp(file[r], "NAND") == 0) {
            r++;
            strcpy(word, file[r]);
            int var1 = searchOrder(variables, word);
            if(var1-2 > inputs) {
                var1 = var1 - outputs;
            }
            else if(var1 < 0) {
                char *ptr;
                var1 = (int)strtol(word, &ptr, 10);
            }
            r++;
            strcpy(word, file[r]);
            int var2 = searchOrder(variables, word);
            if(var2-2 > inputs) {
                var2 = var2 - outputs;
            }
            else if(var2 < 0) {
                char *ptr2;
                var2 = (int)strtol(word, &ptr2, 10);
            }
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int var3 = searchOrder(variables, word);
            int *temp3 = (int*)malloc((size) * sizeof(int));
            for(int i = 0; i < size; i ++) {
               int x;
                int y;
                if(var1 < 2) {
                    x = var1;
                }
                else {
                    x = inputArr[var1-2][i];
                }
                if(var2 < 2) {
                    y = var2;
                } 
                else {
                    y = inputArr[var2-2][i];
                }
                temp3[i] = nand(x, y);
            }
            pushArr(variables, var3, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var3, size);
        }
        else if(strcmp(file[r], "XOR") == 0) {
            r++;
            strcpy(word, file[r]);
            int var1 = searchOrder(variables, word);
            if(var1-2 > inputs) {
                var1 = var1 - outputs;
            }
            else if(var1 < 0) {
                if(strcmp(word, "1") != 0 || strcmp(word, "0") != 0) {
                    int u = r-1;
                    file = realloc(file, (tot+4)*sizeof(char*));
                    for(int j = tot; j < tot+4; j++) {
                        file[j] = (char*)malloc((16)*sizeof(char));
                        strcpy(file[j], file[u]);
                        u++;
                    }
                    tot = tot+4;
                    continue;
                }
                else {
                    char *ptr;
                    var1 = (int)strtol(word, &ptr, 10);
                }
            }
            r++;
            strcpy(word, file[r]);
            int var2 = searchOrder(variables, word);
            if(var2-2 > inputs) {
                var2 = var2 - outputs;
            }
            else if(var2 < 0) {
                char *ptr2;
                var2 = (int)strtol(word, &ptr2, 10);
            }
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int var3 = searchOrder(variables, word);
            int *temp3 = (int*)malloc((size) * sizeof(int));           
            for(int i = 0; i < size; i ++) {
                int x;
                int y;
                if(var1 < 2) {
                    x = var1;
                }
                else {
                    x = inputArr[var1-2][i];
                }
                if(var2 < 2) {
                    y = var2;
                } 
                else {
                    y = inputArr[var2-2][i];
                }
                temp3[i] = xor(x, y);
            }
            pushArr(variables, var3, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var3, size);
        }
        else if(strcmp(file[r], "OR") == 0) {
            r++;
            strcpy(word, file[r]);
            int var1 = searchOrder(variables, word);
            if(var1-2 > inputs) {
                var1 = var1 - outputs;
            }
            else if(var1 < 0) {
                char *ptr;
                var1 = (int)strtol(word, &ptr, 10);
            }
            r++;
            strcpy(word, file[r]);
            int var2 = searchOrder(variables, word);
            if(var2-2 > inputs) {
                var2 = var2 - outputs;
            }
            else if(var2 < 0) {
                char *ptr2;
                var2 = (int)strtol(word, &ptr2, 10);
            }
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int var3 = searchOrder(variables, word);
            int *temp3 = (int*)malloc((size) * sizeof(int));           
            for(int i = 0; i < size; i ++) {
                int x;
                int y;
                if(var1 < 2) {
                    x = var1;
                }
                else {
                    x = inputArr[var1-2][i];
                }
                if(var2 < 2) {
                    y = var2;
                } 
                else {
                    y = inputArr[var2-2][i];
                }
                temp3[i] = or(x, y);
            }
            pushArr(variables, var3, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var3, size);
        }
        else if(strcmp(file[r], "NOR") == 0) {
            r++;
            strcpy(word, file[r]);
            int var1 = searchOrder(variables, word);
            if(var1-2 > inputs) {
                var1 = var1 - outputs;
            }
            else if(var1 < 0) {
                if(strcmp(word, "1") != 0 || strcmp(word, "0") != 0) {
                    int u = r-1;
                    file = realloc(file, (tot+4)*sizeof(char*));
                    for(int j = tot; j < tot+4; j++) {
                        file[j] = (char*)malloc((16)*sizeof(char));
                        strcpy(file[j], file[u]);
                        u++;
                    }
                    tot = tot+4;
                    continue;
                }
                else {
                    char *ptr;
                    var1 = (int)strtol(word, &ptr, 10);
                }
            }
            r++;
            strcpy(word, file[r]);
            int var2 = searchOrder(variables, word);
            if(var2-2 > inputs) {
                var2 = var2 - outputs;
            }
            else if(var2 < 0) {
                char *ptr2;
                var2 = (int)strtol(word, &ptr2, 10);
            }
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int var3 = searchOrder(variables, word);
            int *temp3 = (int*)malloc((size) * sizeof(int));
            for(int i = 0; i < size; i ++) {
                int x;
                int y;
                if(var1 < 2) {
                    x = var1;
                }
                else {
                    x = inputArr[var1-2][i];
                }
                if(var2 < 2) {
                    y = var2;
                } 
                else {
                    y = inputArr[var2-2][i];
                }
                temp3[i] = nor(x, y);
            }
            pushArr(variables, var3, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var3, size);
        }
        else if(strcmp(file[r], "NOT") == 0) {
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                int u = r-1;
                file = realloc(file, (tot+3)*sizeof(char*));
                for(int j = tot; j < tot+3; j++) {
                    file[j] = (char*)malloc((16)*sizeof(char));
                    strcpy(file[j], file[u]);
                    u++;
                }
                tot = tot+3;
                continue;
            }
            int var1 = searchOrder(variables, word);
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int *temp3 = (int*)malloc((size) * sizeof(int));   
            int var3 = searchOrder(variables, word);
            for(int k = 0; k < size; k++) {
                int x = inputArr[var1-2][k];
                temp3[k] = not(x);
            }
            pushArr(variables, var3, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var3, size);
        }
        else if(strcmp(file[r], "PASS") == 0) {
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                int u = r-1;
                file = realloc(file, (tot+3)*sizeof(char*));
                for(int j = tot; j < tot+3; j++) {
                    file[j] = (char*)malloc((16)*sizeof(char));
                    strcpy(file[j], file[u]);
                    u++;
                }
                tot = tot+3;
                continue;
            }
            int var1 = searchOrder(variables, word);
            int *temp = searchArr(variables, var1, size);
            r++;
            strcpy(word, file[r]);
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int var2 = searchOrder(variables, word);
            pushArr(variables, var2, temp);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, var2, size);
        }
        else if(strcmp(file[r], "MULTIPLEXER") == 0) {
            char *z;
            r++;
            int length = (int)strtol(file[r], &z, 10);
            int length2 = (int)pow(2,length);
            int *m = (int*)malloc((length2) * sizeof(int));
            int *temp = (int*)malloc((length) * sizeof(int));
            for(int k = 0; k < length2; k++) {
                r++;
                strcpy(word, file[r]);
                if(searchOrder(variables, word) == -1) {
                    char *ptr;
                    m[k] = (int)strtol(word, &ptr, 10);
                } 
                else {
                    m[k] = searchOrder(variables, word);
                } 
            }
            for(int k = 0; k < length; k++) {
                r++;
                strcpy(word, file[r]);
                temp[k] = searchOrder(variables, word); 
            }
            r++;
            strcpy(word, file[r]);
            int *temp3 = (int*)malloc((size) * sizeof(int));
            if(searchOrder(variables, word) == -1) {
                pushVar(&variables, word,inputs+outputs+count+2,inputs);
            }
            int newNum = searchOrder(variables, word);
            int *d = (int*)malloc((length2) * sizeof(int));
            for(int j = 0; j <length2; j++) {
                d[j] = m[j];
            }
            for(int i = 0; i < length; i++) {
                if(temp[i]-2 > inputs+outputs) {
                    temp[i] = temp[i]-outputs;
                }
            }
            int *row = (int*)malloc((length) * sizeof(int));
            for(int k = 0; k < size; k++) {
                for(int j = 0; j < length2; j++) {
                    if(m[j] > 1) {
                        int t = m[j]-3;
                        d[j] = inputArr[t][k];
                    }
                }
                for(int i = 0; i < length; i++) {
                    row[i] = inputArr[(temp[i]-2)][k];
                }
                temp3[k] = multiplex(d, row, length);
            }
            pushArr(variables, newNum, temp3);
            count++;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            inputArr[inputs+count-1] = searchArr(variables, newNum, size);
            free(temp);
            free(m);
            free(d);
            free(row);  
        }
        else if(strcmp(file[r], "DECODER") == 0) {
            char *z;
            r++;
            int length = (int)strtol(file[r], &z, 10);
            int length2 = (int)pow(2,length);
            int tempCount = length2;
            int *m = (int*)malloc((length2) * sizeof(int));
            int *d = (int*)malloc((length2) * sizeof(int));
            int *temp = (int*)malloc((length) * sizeof(int));
            for(int i = 0; i < length; i++) {
                r++;
                strcpy(word, file[r]);
                temp[i] = searchOrder(variables, word);
            }
            for(int i = 0; i < length2; i++) {
                r++;
                strcpy(word, file[r]);
                if(searchOrder(variables, word) == -1) {
                    pushVar(&variables, word,inputs+outputs+count+i+2,inputs);
                }
                d[i] = searchOrder(variables, word);
                m[i] = searchOrder(variables, word);
            }
            for(int i = 0; i < length; i++) {
                if(temp[i]-2 > inputs) {
                    temp[i] = temp[i]-outputs;
                }
            }
            for(int i = 0; i < length2; i++) {
                if(m[i]-2 > inputs+outputs) {
                    m[i] = m[i]-outputs;
                }
            }
            int *row = (int*)malloc((length) * sizeof(int));
            int **temp3 = (int**)malloc((size) * sizeof(int*));
            for(int k = 0; k < size; k++) {
                temp3[k] = (int*)malloc((length2) * sizeof(int));
            }
            for(int k = 0; k < size; k++) {
                for(int i = 0; i < length; i++) {
                    for(int j = 0; j < inputs+count; j++) {
                        if(j == temp[i]-2) {
                            row[i] = inputArr[j][k];
                        }
                    }
                }
                for(int j = 0; j < length2; j++) {
                    temp3[k][j] = decoder(row, length, j);
                }
            }
            int **temp4 = (int**)malloc((length2) * sizeof(int*));
            for(int k = 0; k < length2; k++) {
                temp4[k] = (int*)malloc((size) * sizeof(int));
            }
            for(int i = 0; i < length2; i ++) {
                for(int j = 0; j < size; j++) {
                    temp4[i][j] = temp3[j][i];
                }
            }
            count = count+length2;
            inputArr = realloc(inputArr,(inputs+count)*sizeof(int*));
            for(int i =0; i < length2; i++) {
                pushArr(variables, d[i], temp4[i]);
                inputArr[inputs+count-tempCount+i] = searchArr(variables, d[i], size);
            }
            for(int k = 0; k < size; k++) {
                free(temp3[k]);
            }
            free(d);
            free(temp3);
            free(temp4);
            free(temp);
            free(m);
            free(row);
        }
        r++;
    }
    int**arr = (int**)malloc((inputs)*sizeof(int*));
    for (int i = 0; i < inputs; i++) {
        arr[i] = searchArr(variables, i+2, size);
    }
    int** outArr = (int**)malloc((outputs)*sizeof(int*));
    for (int i = 0; i < outputs; i++) {
        outArr[i] = searchArr(variables, inputs+i+2, size);
    }
    for(int j = 0; j < size; j++) {
        for(int i = 0; i < inputs+outputs+1; i++) {
            if(i == 0) {
                printf("%d", arr[i][j]);
            }
            else if(i < inputs) {
                printf(" %d", arr[i][j]);
            }
            else if(i > inputs) {
                printf(" %d", outArr[(i-1-inputs)][j]);
            }
            else {
                printf(" |");
            }
        }
        printf("\n");
    }
    while(variables) {
		pop(&variables);
	}
    for(int i = 0; i < inputs+count; i++) {
        free(inputArr[i]);
    }
    for(int i = 0; i < inputs; i++) {
        free(arr[i]);
    }
    for(int i = 0; i < outputs; i++) {
        free(outArr[i]);
    }
    for(int i = 0; i < tot; i++) {
        free(file[i]);
    }
    free(file);
    free(inputArr);
    free(arr);
    free(outArr);
}
