#include <iostream>
#include <vector>
#include <iomanip>

void CreateMatrix(std::vector<std::vector<double> >& matrix, std::vector<double>& B_matrix, const int N){
    int i = 0;
    int j = 0;
    double size = static_cast<double>(N);
    while(i < size){
        B_matrix[i] = static_cast<double>(25*i) + size;
        while(j < size){
            if(i == j){
                matrix[i][j] = size + 90 + i/size + j/15;
                std::cout << std::setw(9) << matrix[i][j] << "|";
            } else{
                matrix[i][j] = static_cast<double>(i + j) / (20 + size);
                std::cout << std::setw(9) << matrix[i][j] << "|";
            }
            j++;
        }
        std::cout << '\n';
        i++;
        j = 0;
    }
    for(auto i : B_matrix){
        std::cout << i << " ";
    }
    std::cout << '\n';
    std::cout <<"Done! \n";
}

void SeidelMethod(std::vector<std::vector<double> >& a,
                std::vector<double>& B_matrix, const int n){
    for(int i = 0; i < n; i++){
        a[i].push_back(B_matrix[i]);
    }
    std::vector<double> x(n, 0); //initial variable's values
    double eps, y;
    int i, j, k, flag = 0, count = 0;

    std::cout << "Enter epsilon value: ";
    std::cin >> eps;

        for (i=0;i<n;i++)                    //Pivotisation(partial) to make the equations diagonally dominant
        for (k=i+1;k<n;k++)
            if (abs(a[i][i])<abs(a[k][i]))
                for (j=0;j<=n;j++)
                {
                    double temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
    std::cout<<"Iter"<<std::setw(5);
    for(i=0;i<n;i++)
        std::cout<<"x"<<i<<std::setw(8);
    std::cout<<"\n---------------------------------------------------------------------------------------------------------------";
    do                            //Perform iterations to calculate x1,x2,...xn
    {
        std::cout<<"\n"<<count+1<<"."<<std::setw(9);
        for (i=0;i<n;i++)                //Loop that calculates x1,x2,...xn
        {
            y=x[i];
            x[i]=a[i][n];
            for (j=0;j<n;j++)
            {
                if (j!=i)
                x[i]=x[i]-a[i][j]*x[j];
            }
            x[i]=x[i]/a[i][i];
            if (abs(x[i]-y)<=eps)            //Compare the ne value with the last value
                flag++;
            std::cout<<x[i]<<std::setw(9);
        }
        std::cout<<"\n";
        count++;   
    }while(flag<n);                        //If the values of all the variables don't differ from their previious values with error more than eps then flag must be n and hence stop the loop
    
    std::cout<<"\n The solution is as follows:\n";
    for (i=0;i<n;i++)
        std::cout<<"x"<<i<<" = "<<x[i]<<std::endl;  



   /* for(i = 0; i < N; i++){
        for(k=i+1; k<N; k++){
            if(abs(matrix[i][i]) < abs(matrix[k][i])){
                for(j = 0; j<= N; j++){
                    double temp = matrix[i][j];
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = temp;
                }
            }
        }
    }
    std::cout << "Iter: " << std::setw(5);
    for(i = 0; i < N; i++){
        std::cout << "x" << i << std::setw(8);
    }
    std::cout << "\n----------------------------------------------------------------";
    
    do{
        std::cout << "\n" << count + 1 << "." << std::setw(16);
        for(i = 0; i < N; i++){
            y = x[i];
            x[i] = matrix[i][N];
            for(j = 0; j < N; j++){
                if(j != i){
                    x[i] = x[j] - matrix[i][j] * x[j];
                }
            }
            x[i] = x[i] / matrix[i][i];
            if(abs(x[i] - y) <= eps){
                flag++;
            }
            std::cout << x[i] << std::setw(18);
        }
        std::cout << "\n";
        count++;
    }while(flag < N);
    std::cout << "\nThe solution is as follows:\n";
    for(int i = 0; i < N; i++){
        std::cout << "x" << i << " = " << x[i] << std::endl;
    }
    */
}

int main(){
    std::cout.precision(4);
    std::cout.setf(std::ios::fixed);
    int N;
    std::cout << "Put N size for matrix:\n";
    std::cin >> N;
    std::vector<double> B_matrix(N, 0);
    //std::cout << B_matrix.size() << std::endl;
    std::vector< std::vector<double> > matrix(N, std::vector<double>(N, 0));
    CreateMatrix(matrix, B_matrix, N);
    SeidelMethod(matrix, B_matrix, N);
    return 0;
}