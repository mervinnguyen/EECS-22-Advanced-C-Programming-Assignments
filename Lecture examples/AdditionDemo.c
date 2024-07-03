/* AdditionDemo.c: adding two integer numbers */

int main(void){
    int a;
    int b; 
    int sum;

    printf("Enter the first number: ");
    scanf("%d", &a);

    printf("Enter the second number: ");
    scanf("%d", &b);       //take a second number and store it into the address at b

    sum = a + b;

    printf("The sum of %d and %d is %d\n", a, b, sum);  // \n inside the quotations
    return 0;

}
