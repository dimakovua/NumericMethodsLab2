#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
void Nevyazka_idk_know_how_to_call_it(std::vector<std::vector<double> >& matrix, std::vector<double>& b, std::vector<double>& val){
    const int SIZE = b.size();
    std::vector<double> r;
    int i = 0, j = 0;
    for(i = 0; i < SIZE; i++){
        double sum = 0;
        for(j = 0; j < SIZE; j++){
            sum+=matrix[i][j] * val[j];
        }
        r.push_back(sum - b[i]);
        j = 0;
        
    }
    std::cout << "\nNevyazka:\n";
    for(auto i : r){
        std::cout << i << " ";
    }
    std::cout << "\n";
}
void CalculateSD(std::vector<std::vector<double> >& S, std::vector<std::vector<double> >& D, std::vector<std::vector<double> >& A, double& determinant){
    S[0][0] = sqrt(abs(A[0][0]));
    D[0][0] = sgn(A[0][0]);
    for(int i = 1; i < 4; i++){
        double sum = 0;
        for(int p = 0; p < i; p++){
            sum+= pow(S[p][i], 2) * D[p][p];
        }
        D[i][i] = sgn(A[i][i] - sum);
        S[i][i] = sqrt(abs(A[i][i] - sum));
        if(i!=3){
            for(int j = i+1; j <4; j++){
                double sum1 = 0;
                for(int p = 0; p < i; p++){
                    sum1 += S[p][i] * D[p][p] * S[p][j];
                }
                S[i][j] = (A[i][j] - sum1) / (D[i][i] * S[i][i]);
            }
        }
    }
    for(int i = 0; i < 4; i++){
        determinant *= D[i][i] * pow(S[i][i], 2);
    }
    std::cout << "Determinant = " << determinant << std::endl;
}
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
void SquareMethod(){
    std::vector<std::vector<double> > Matrix (4, std::vector<double>(4,0));
    std::vector<std::vector<double> > S (4, std::vector<double>(4,0));
    std::vector<std::vector<double> > D (4, std::vector<double>(4,0));
    double determinant = 1;
    double eps = 0.0001;

    std::vector<double> B_vec(4,0);
    CreateMatrix(Matrix, B_vec, 4);
    CalculateSD(S, D, Matrix, determinant);

    std::vector<std::vector<double> > St(4, std::vector<double>(4,0));
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            St[i][j] = S[j][i];
        }
    }

    std::vector<std::vector<double> > StD = St;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            StD[i][j] = 0.0;
            for(int k = 0; k < 4; k++){
                StD[i][j] += St[i][k] * D[k][j];
            }
        }
    }

    std::vector<double> y(4,0);
    y[0] = (B_vec[0] / StD[0][0]);
    y[1] = ((B_vec[1] - y[0] * StD[1][0]) / StD[1][1]);
    y[2] = ((B_vec[2] - y[0] * StD[2][0] - y[1] * StD[2][1]) / StD[2][2]);
    y[3] = ((B_vec[3] - y[0] * StD[3][0] - y[1] * StD[3][1] - y[2] * StD[3][2]) / StD[3][3]);
    std::cout << "y vector:\n";
    for(auto i : y){
        std::cout << i << '\t';
    }
    std::cout << "\n";

    std::vector<double> x(4,0);
    x[3] = (y[3] / S[3][3]);
    x[2] = ((y[2] - x[3] * S[2][3]) / S[2][2]);
    x[1] = ((y[1] - x[3] * S[1][3] - x[2] * S[1][2]) / S[1][1]);
    x[0] = ((y[0] - x[3] * S[0][3] - x[2] * S[0][2] - x[1] * S[0][1]) / S[0][0]);
    std::cout << "x vector:\n";
    for(auto i : x){
        std::cout << i << '\t';
    }
    std::cout << "\n";

    Nevyazka_idk_know_how_to_call_it(Matrix, B_vec, x);

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
    Nevyazka_idk_know_how_to_call_it(a, B_matrix, x);
}

int main(){
    std::cout.precision(6);
    std::cout.setf(std::ios::fixed);
    int N;
    std::string answer;
    std::cout << "Put S for SQRT or SS for Seidel: ";
    std::cin >> answer;
    std::cout << "Put N size for matrix:\n";
    std::cin >> N;
    std::vector<double> B_matrix(N, 0);
    //std::cout << B_matrix.size() << std::endl;
    std::vector< std::vector<double> > matrix(N, std::vector<double>(N, 0));
    CreateMatrix(matrix, B_matrix, N);
    if(answer == "SS") SeidelMethod(matrix, B_matrix, N);
    if(answer == "S") SquareMethod();
    return 0;
}