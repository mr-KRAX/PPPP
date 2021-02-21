#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


/**
 * @brief Вернуть новую пустую матрицу размерности NxM
 * 
 * @param N кол-во строк (N)
 * @param M кол-во столбцов (M)
 * @return int** Указатель на начало матрицы или nullptr, если введены некорректные параметры
 */
int **newMatrix(int N, int M) {
  if (N <= 0 || M <= 0)
    return nullptr;

  int **matrix = new int *[N];
  for (int i = 0; i < N; i++) {
    matrix[i] = new int[M];
  }
  return matrix;
}

/**
 * @brief Получить размерность матрицы (неотрицательные значения N и M) от пользователя
 * 
 * @param msg Сообщение, которое будет передано пользователю перед вводом значений
 * @param N Кол-во строк
 * @param M Колво столбцов
 */
void getMatrixDimensionsFromUser(const char *msg, int *N, int *M) {
  cout << msg << endl;
  int n, m;
  while (true) {
    cout << "N: ";
    cin >> n;
    cout << "M: ";
    cin >> m;

    if (n <= 0 || m <= 0) {
      cout << "Некорректный ввод, попробуйте еще раз!" << endl;
      continue;
    }
    break;
  }
  *N = n;
  *M = m;
}

/**
 * @brief Заполнить матрицу размером M x N рандомными значениями от 0 до 10 (исключая)
 * 
 * @param matrix Матрица
 * @param N Кол-во строк
 * @param M Кол-во столбцов
 */
void fillMatrixWithRandom(int **matrix, int N, int M) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      matrix[i][j] = rand() % 10;
}

/**
 * @brief Заполнить матрицу размером M x N нулями
 * 
 * @param matrix Матрица
 * @param N Кол-во строк
 * @param M Кол-во столбцов
 */
void fillMatrixWithZeros(int **matrix, int N, int M) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      matrix[i][j] = 0;
};

/**
 * @brief Заполнить матрицу размером M x N значениями полученными от пользователя
 * 
 * @param matrix Матрица
 * @param N Кол-во строк
 * @param M Кол-во столбцов
 * @param msg Сообщение, которое будет выведено пользователю перед вводом матрицы
 */
void fillMatrixByUser(int **matrix, int N, int M, const char *msg) {
  cout << msg << endl;
  for (int i = 0; i < N; i++) {
    cout << "Введите " << M << " значен(-ий, -е, -я) " << i << "-й строки" << endl;
    for (int j = 0; j < M; j++)
      cin >> matrix[i][j];
  }
}

/**
 * @brief Вывести матрицу
 * 
 * @param matrix Матрица
 * @param N Кол-во строк
 * @param M Кол-во столбцов
 * @param msg Сообщение, которое будет выведено перед матрицей (может быть nullptr)
 */
void printMatrix(int **matrix, int N, int M, const char *msg) {
  cout << msg << endl;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
}

/**
 * @brief Найти минимальное число равное степени двойки,
 *        которое больше n1, m1, n2, m2
 */
int minCommonPowOf2(int n1, int m1, int n2, int m2) {
  int m = max(max(n1, m1), max(n2, m2));
  int L = 2;
  while (L < m)
    L *= 2;
  return L;
}

/**
 * @brief Дополнить матрицу нулевыми столбцами и строками до нцжного размера
 * 
 * @param matr_src матрица 
 * @param N_src кол-во строк до
 * @param M_src кол-во столбцов до
 * @param N_res кол-во строк после
 * @param M_res кол-во столбцов после
 * @return int** Новая матрица, резульнат оперции
 */
int **extendMatrix(int **matr_src, int N_src, int M_src, int N_res, int M_res) {
  int **matr_res = newMatrix(N_res, M_res);
  fillMatrixWithZeros(matr_res, N_res, M_res);
  for (int i = 0; i < N_src; i++)
    for (int j = 0; j < M_src; j++)
      matr_res[i][j] = matr_src[i][j];
  return matr_res;
}

/**
 * @brief Убрать крайние нулевые столбцы и строки
 * 
 * @param matr_src матрица 
 * @param N_src кол-во строк до
 * @param M_src кол-во столбцов до
 * @param N_res кол-во строк после
 * @param M_res кол-во столбцов после
 * @return int** Новая матрица, резульнат оперции
 */
int **shrinkMatrix(int **matr_src, int N_src, int M_src, int *N_res, int *M_res) {
  int newN = N_src;
  int newM = M_src;

  for (int i = N_src - 1; i >= 0; i--) {
    bool notZero = false;
    for (int j = 0; j < M_src; j++)
      if (matr_src[i][j] != 0) {
        notZero = true;
        break;
      }
    if (notZero)
      break;
    newN--;
  }

  for (int j = M_src - 1; j >= 0; j--) {
    bool notZero = false;
    for (int i = 0; i < N_src; i++)
      if (matr_src[i][j] != 0) {
        notZero = true;
        break;
      }
    if (notZero)
      break;
    newM--;
  }

  int **matrRes = newMatrix(newN, newM);
  for (int i = 0; i < newN; i++)
    for (int j = 0; j < newM; j++)
      matrRes[i][j] = matr_src[i][j];
  *N_res = newN;
  *M_res = newM;
  return matrRes;
}


/**
 * @brief Стандартные математические операции надо двумя одинаковыми квадратными матрицами
 *        вида: (A t B), где t из { +, -, *}
 * 
 * @param A матрица А
 * @param B матрица И
 * @param dim размерность матриц
 * @return int** новая матрица, результат операции
 */
int **add(int **A, int **B, int dim) {
  int **matr_res = newMatrix(dim, dim);
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      matr_res[i][j] = A[i][j] + B[i][j];
  return matr_res;
}

int **substract(int **A, int **B, int dim) {
  int **matr_res = newMatrix(dim, dim);
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      matr_res[i][j] = A[i][j] - B[i][j];
  return matr_res;
}

int **multiply(int **A, int **B, int dim) {
  int **matr_res = newMatrix(dim, dim);

  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++) {
      matr_res[i][j] = 0;
      for (int z = 0; z < dim; z++)
        matr_res[i][j] += A[i][z] * B[z][j];
    }

  return matr_res;
}

/**
 * @brief Получить прямоугольны сегмент матрицы 
 * 
 * @param matr_src исхоная матрица
 * @param i1 верхняя граница сегмента (включая)
 * @param j1 левая граница сегмента (включая)
 * @param i2 нижняя граница сегмента (исключая)
 * @param j2 правая граница сегмента (исключая)
 * @return int** новая матрица значения которой равны значению сегмента
 */
int **getMatrixPartition(int **matr_src, int i1, int j1, int i2, int j2) {
  int **res_matr = newMatrix(i2 - i1 + 1, j2 - j1 + 1);
  for (int i = i1; i < i2; i++)
    for (int j = j1; j < j2; j++)
      res_matr[i - i1][j - j1] = matr_src[i][j];
  return res_matr;
}

/**
 * @brief Освободить память выделенную под матрицу
 * 
 * @param matrix 
 * @param N 
 * @param M 
 */
void freeMatrix(int **matrix, int N, int M) {
  for (int i = 0; i < N; i++)
    delete[] matrix[i];
  delete matrix;
}

/**
 * @brief Перемножить матрицы с помощью алгоритма Штрасса
 *        Матрицы должны быть одинкаово размерности степени двух
 * 
 * @param matr_A Матрица А
 * @param matr_B Матрица В
 * @param dim размерность (2^k)
 * @return int** Результирующая матрица
 */
int **multiplyByStrassenAlg(int **matr_A, int **matr_B, int dim) {
  /**
   * Разбиение матриц на подматрицы и их заполнение
   */
  int L = dim / 2;
  int **A11 = getMatrixPartition(matr_A, 0, 0, L, L);
  int **A12 = getMatrixPartition(matr_A, 0, L, L, 2 * L);
  int **A21 = getMatrixPartition(matr_A, L, 0, 2 * L, L);
  int **A22 = getMatrixPartition(matr_A, L, L, 2 * L, 2 * L);

  int **B11 = getMatrixPartition(matr_B, 0, 0, L, L);
  int **B12 = getMatrixPartition(matr_B, 0, L, L, 2 * L);
  int **B21 = getMatrixPartition(matr_B, L, 0, 2 * L, L);
  int **B22 = getMatrixPartition(matr_B, L, L, 2 * L, 2 * L);

  /**
   * Вычисление значений промежуточных матриц
   */
  int **S1, **S2;
  int **P1, **P2, **P3, **P4, **P5, **P6, **P7;

  // (A11 + A22)(B11 + B22)
  S1 = add(A11, A22, L);
  S2 = add(B11, B22, L);
  P1 = multiply(S1, S2, L);
  freeMatrix(S1, L, L);
  freeMatrix(S2, L, L);

  // (A21 + A22)B11
  S1 = add(A21, A22, L);
  P2 = multiply(S1, B11, L);
  freeMatrix(S1, L, L);

  // A11(B12 - B22)
  S2 = substract(B12, B22, L);
  P3 = multiply(A11, S2, L);
  freeMatrix(S2, L, L);

  // A22(B21 - B11)
  S2 = substract(B21, B11, L);
  P4 = multiply(A22, S2, L);
  freeMatrix(S2, L, L);

  // (A11 + A12)B22
  S1 = add(A11, A12, L);
  P5 = multiply(S1, B22, L);
  freeMatrix(S1, L, L);

  // (A21 - A11)(B11 + B12)
  S1 = substract(A21, A11, L);
  S2 = add(B11, B12, L);
  P6 = multiply(S1, S2, L);
  freeMatrix(S1, L, L);
  freeMatrix(S2, L, L);

  // (A12 - A22)(B21 + B22)
  S1 = substract(A12, A22, L);
  S2 = add(B21, B22, L);
  P7 = multiply(S1, S2, L);
  freeMatrix(S1, L, L);
  freeMatrix(S2, L, L);

  /**
   * Подсчет значений вспомогательных матриц из промежуточных
   */

  int **C11, **C12, **C21, **C22;

  // P1 + P4 - P5 + P7
  S1 = add(P1, P4, L);
  S2 = substract(S1, P5, L);
  C11 = add(S2, P7, L);
  freeMatrix(S1, L, L);
  freeMatrix(S2, L, L);


  // P3 + P5
  C12 = add(P3, P5, L);

  // P2 + P4
  C21 = add(P2, P4, L);

  // P1 - P2 + P3 + P6
  S1 = substract(P1, P2, L);
  S2 = add(S1, P3, L);
  C22 = add(S2, P6, L);
  freeMatrix(S1, L, L);
  freeMatrix(S2, L, L);
  
  freeMatrix(P1, L, L);
  freeMatrix(P2, L, L);
  freeMatrix(P3, L, L);
  freeMatrix(P4, L, L);
  freeMatrix(P5, L, L);
  freeMatrix(P6, L, L);
  freeMatrix(P7, L, L);

  /**
   * Создание результирующей матрицы
   */
  int **matr_C = newMatrix(2 * L, 2 * L);
  for (int i = 0; i < L; i++)
    for (int j = 0; j < L; j++) {
      matr_C[i][j] = C11[i][j];
      matr_C[i][L + j] = C12[i][j];
      matr_C[L + i][j] = C21[i][j];
      matr_C[L + i][L + j] = C22[i][j];
    }

  freeMatrix(C11, L, L);
  freeMatrix(C12, L, L);
  freeMatrix(C21, L, L);
  freeMatrix(C22, L, L);
  return matr_C;
}


int main() {
  // system("chcp 1251");
  cout << "Вас приветствует программа" << endl
       << "быстрого перемножения матриц методом Штрассена" << endl
       << endl;

  srand(time(NULL));


  /**
   * Ввод размеров матрицы пользователем
   */

  // Размерности матриц A и B
  int n_A, m_A, n_B, m_B;
  getMatrixDimensionsFromUser("Введите размеры первой матрицы", &n_A, &m_A);
  getMatrixDimensionsFromUser("Введите размеры второй матрицы", &n_B, &m_B);
  int **matr_A = newMatrix(n_A, m_A);
  int **matr_B = newMatrix(n_B, m_B);


  /**
   * Инициализация матриц значениями
   */

  int user_op;
  while (true) {
    cout << "Выберите способ заполнения матриц" << endl
         << "1 - Вручную" << endl
         << "2 - Случайным образом" << endl;
    cin >> user_op;
    if (user_op < 1 || user_op > 2) {
      cout << "Не верная опция!" << endl;
      continue;
    }
    break;
  }

  switch (user_op) {
  case 1:
    fillMatrixByUser(matr_A, n_A, m_A, "\nВведите первую матрицу");
    fillMatrixByUser(matr_B, n_B, m_B, "Введите вторую матрицу");
    break;
  case 2:
    fillMatrixWithRandom(matr_A, n_A, m_A);
    fillMatrixWithRandom(matr_B, n_B, m_B);
    break;
  }
  printMatrix(matr_A, n_A, m_A, "\nМатрица 1");
  printMatrix(matr_B, n_B, m_B, "Матрица 2");


  /**
   * Приведение матриц к требуемому размеру
   */

  // Размерность приведенных матриц
  int new_dim = minCommonPowOf2(n_A, m_A, n_B, m_B);

  int** matr_A_ext = extendMatrix(matr_A, n_A, m_A, new_dim, new_dim);
  int** matr_B_ext = extendMatrix(matr_B, n_B, m_B, new_dim, new_dim);
  printMatrix(matr_A_ext, new_dim, new_dim, "\nПриведенные матрицы\n\nМатрица 1");
  printMatrix(matr_B_ext, new_dim, new_dim, "Матрица 2");

  freeMatrix(matr_A, n_A, m_A);
  freeMatrix(matr_B, n_B, m_B);



  /**
   * Вычисление произведения
   */

  int **matr_C_ext = multiplyByStrassenAlg(matr_A_ext, matr_B_ext, new_dim);
  int n_C, m_C;

  int** matr_C = shrinkMatrix(matr_C_ext, new_dim, new_dim, &n_C, &m_C);
  printMatrix(matr_C, n_C, m_C, "\nРезультирующая матрица:"); 


  freeMatrix(matr_A_ext, new_dim, new_dim);
  freeMatrix(matr_B_ext, new_dim, new_dim);
  freeMatrix(matr_C_ext, new_dim, new_dim);
  freeMatrix(matr_C, n_C, m_C);

  // system("pause");

  return 0;
}