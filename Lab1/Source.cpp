#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

/**
 * @brief Вернуть новую матрицу размерности NxM
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

int **newSquareMatrix(int N) {
	return newMatrix(N, N);
}

/**
 * @brief Вернуть нулевую матрицу N х N
 * 
 * @param N размерность
 * @return int** Указатель на начало матрицы или nullptr, если введены некорректные параметры
 */
int **newSquareZeroMatrix(int N){
	if (N <= 0)
    return nullptr;

  int **matrix = new int *[N];
  for (int i = 0; i < N; i++) {
    matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			matrix[i][j] = 0;
  }
  return matrix;
}

/**
 * @brief Скопировать матрицу src в матрицу dst
 * 				Пользоватьель должен убедиться что в dst достаточно места
 * 
 * @param src Матрица источник
 * @param srcN Кол-во строк в src
 * @param srcM Кол-во столбцов в src
 * @param dst Матрица приемник
 */
void copyMatrix(int** src, int srcN, int srcM, int** dst){
  for (int i = 0; i < srcN; i++) {
    for (int j = 0; j < srcM; j++)
      dst[i][j] = src[i][j];
  }
}

void copyMatrixPart(int** src, int offsetN, int offsetM, int N, int M, int** dst){
}
/**
 * @brief Получить размерность матрицы (неотрицательные значения N и M) от пользователя
 * 
 * @param msg Сообщение, которое будет передано пользователю перед вводом значений
 * @param N Кол-во строк
 * @param M Колво столбцов
 */
void getMatrixdimensionsFromUser(const char *msg, int *N, int *M) {
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
void fillMatrixRandomly(int **matrix, int N, int M) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      matrix[i][j] = rand() % 10;
}

/**
 * @brief Заполнить матрицу размером M x N значениями полученными от пользователя
 * 
 * @param matrix Матрица
 * @param N Кол-во строк
 * @param M Кол-во столбцов
 * @param msg Сообщение, которое будет выведено пользователю перед вводом матрицы
 */
void fillMatrixFromUser(int **matrix, int N, int M, const char* msg) {
	cout << msg << endl;
  for (int i = 0; i < N; i++){
		cout << "Введите " << M << "значений " << i << "-й строки" << endl;
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

void main() {
  srand(time(NULL));
  int n1, m1, n2, m2, k, l = 2;
  // system("chcp 1251");
  cout << "Вас приветствует программа" << endl
       << "быстрого перемножения матриц методом Штрассена" << endl
			 << endl;

  ///////////////////////////////////////////////////////////////////////////////
  ////////////////////Ввод размеров матрицы пользователем////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

	getMatrixdimensionsFromUser("Введите размеры первой матрицы", &n1, &m1);
  int** M1 = newMatrix(n1, m1);

	getMatrixdimensionsFromUser("Введите размеры второй матрицы", &n2, &m2);
	int** M2 = newMatrix(n2, m2); 

  ///////////////////////////////////////////////////////////////////////////////
  ////////////////Выбор способа заполнения и заполнение матриц///////////////////
  ///////////////////////////////////////////////////////////////////////////////

  do {
    cout << "Выберите способ заполнения матриц\n"
         << "1 - Вручную \n2 - Случайным образом\n";
    cin >> k;
  } while (k < 1 || k > 2);

	while (true) {
		cout << "Выберите способ заполнения матриц" << endl
         << "1 - Вручную" << endl 
				 << "2 - Случайным образом" << endl;
		if (k < 1 || k > 2) {
			cout << "Не верная опция!" << endl;
			continue;
		}
		break;
	}

  switch (k) {
  case 1:
		fillMatrixFromUser(M1, n1, m1, "Введите первую матрицу");
		fillMatrixFromUser(M2, n2, m2, "Введите вторую матрицу");
    break;
  case 2:
		fillMatrixRandomly(M1, n1, m1);
		fillMatrixRandomly(M2, n2, m2);
    break;
  }
	printMatrix(M1, n1, m1, "Матрица 1");
	printMatrix(M2, n2, m2, "Матрица 2");

  ///////////////////////////////////////////////////////////////////////////////
  /////////////////Приведение матриц к требуемому размеру////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  while (l < n1 || l < n2 || l < m1 || l < m2)
    l *= 2;

  int **squareM1 = newSquareZeroMatrix(l);
	int **squareM2 = newSquareZeroMatrix(l);

	copyMatrix(M1, n1, m1, squareM1);
	copyMatrix(M2, n2, m2, squareM2);

	printMatrix(squareM1, l, l, "Приведенные матрицы\n\nМатрица 1\n");
	printMatrix(squareM2, l, l, "Матрица 2");

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
  ///////////////////////////////////////////////////////////////////////////////

	int ***subM1 = new int**[4];
	for (int i = 0; i < 4; i++){
		subM1[i] = newSquareMatrix(l / 2);
		copyMatrix(squareM1, l/2, l/2, subM1[i]);
	}

	int ***subM2 = new int**[4];
	for (int i = 0; i < 4; i++){
		subM2[i] = newSquareMatrix(l / 2);
		copyMatrix(squareM2, l/2, l/2, subM2[i]);
	}
  int **mat5 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat5[i] = new int[l / 2];
    for (int j = 0; j < l / 2; j++)
      mat5[i][j] = squareM2[i][j];
  }
  int **mat6 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat6[i] = new int[l / 2];
    for (int j = 0; j < l / 2; j++)
      mat6[i][j] = squareM2[i][j + l / 2];
  }
  int **mat7 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat7[i] = new int[l / 2];
    for (int j = 0; j < l / 2; j++)
      mat7[i][j] = squareM2[i + l / 2][j];
  }
  int **mat8 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat8[i] = new int[l / 2];
    for (int j = 0; j < l / 2; j++)
      mat8[i][j] = squareM2[i + l / 2][j + l / 2];
  }

  ///////////////////////////////////////////////////////////////////////////////
  ////////////////////////Создание промежуточных матриц//////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  int **p1 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p1[i] = new int[l / 2];
  }
  int **p2 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p2[i] = new int[l / 2];
  }
  int **p3 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p3[i] = new int[l / 2];
  }
  int **p4 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p4[i] = new int[l / 2];
  }
  int **p5 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p5[i] = new int[l / 2];
  }
  int **p6 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p6[i] = new int[l / 2];
  }
  int **p7 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    p7[i] = new int[l / 2];
  }

  ///////////////////////////////////////////////////////////////////////////////
  ////////////////////Вычисление значений промежуточных матриц///////////////////
  ///////////////////////////////////////////////////////////////////////////////

	int** doTheMath(int **matrix1, int **matrix2, int **matrix3, int **matrix4, ){

	}

  for (int i = 0; i < l / 2; i++) {
    for (int j = 0; j < l / 2; j++) {
      p1[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p1[i][j] += (mat1[i][z] + mat4[i][z]) * (mat5[z][j] + mat8[z][j]);
      }

      p2[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p2[i][j] += (mat3[i][z] + mat4[i][z]) * mat5[z][j];
      }

      p3[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p3[i][j] += mat1[i][z] * (mat6[z][j] - mat8[z][j]);
      }

      p4[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p4[i][j] += mat4[i][z] * (mat7[z][j] - mat5[z][j]);
      }

      p5[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p5[i][j] += (mat1[i][z] + mat2[i][z]) * mat8[z][j];
      }

      p6[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p6[i][j] += (mat3[i][z] - mat1[i][z]) * (mat5[z][j] + mat6[z][j]);
      }

      p7[i][j] = 0;
      for (int z = 0; z < l / 2; z++) {
        p7[i][j] += (mat2[i][z] - mat4[i][z]) * (mat7[z][j] + mat8[z][j]);
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////Создание вспомогательных матриц/////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  int **mat9 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat9[i] = new int[l / 2];
  }
  int **mat10 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat10[i] = new int[l / 2];
  }
  int **mat11 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat11[i] = new int[l / 2];
  }
  int **mat12 = new int *[l / 2];
  for (int i = 0; i < l / 2; i++) {
    mat12[i] = new int[l / 2];
  }

  ///////////////////////////////////////////////////////////////////////////////
  ////////////Подсчет значений вспомогательных матриц из промежуточных///////////
  ///////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < l / 2; i++) {
    for (int j = 0; j < l / 2; j++) {
      mat9[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
      mat10[i][j] = p3[i][j] + p5[i][j];
      mat11[i][j] = p2[i][j] + p4[i][j];
      mat12[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
    }
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////Создание результирующей матрицы/////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  int **M5 = new int *[l];
  for (int i = 0; i < l; i++) {
    M5[i] = new int[l];
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////Занесение информации из вспомогательных матриц в результирующую/////////
  ///////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < l / 2; i++) {
    for (int j = 0; j < l / 2; j++) {
      M5[i][j] = mat9[i][j];
      M5[i][j + l / 2] = mat10[i][j];
      M5[i + l / 2][j] = mat11[i][j];
      M5[i + l / 2][j + l / 2] = mat12[i][j];
    }
  }

  ///////////////////////////////////////////////////////////////////////////////
  ////////////////Выравнивание границ результирующей матрицы/////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  int x = 0, f = 100, s = 100;
  for (int i = 0; i < l; i++) {
    x = 0;
    for (int j = 0; j < l; j++) {
      if (M5[i][j] != 0) {
        x++;
        f = 100;
      }
    }
    if (x == 0 && i < f) {
      f = i;
    }
  }
  for (int i = 0; i < l; i++) {
    x = 0;
    for (int j = 0; j < l; j++) {
      if (M5[j][i] != 0) {
        x++;
        s = 100;
      }
    }
    if (x == 0 && i < s) {
      s = i;
    }
  }

  int **M6 = new int *[f];
  for (int i = 0; i < f; i++) {
    M6[i] = new int[s];
    for (int j = 0; j < s; j++)
      M6[i][j] = M5[i][j];
  }

  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////Вывод результирующей матрицы////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  cout << "\nРезультирующая матрица\n\n";
  for (int i = 0; i < f; i++) {
    for (int j = 0; j < s; j++)
      cout << M6[i][j] << " ";
    cout << endl;
  }

  system("pause");

  ///////////////////////////////////////////////////////////////////////////////
  /////////////////////Очистка динамической памяти///////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < n1; i++)
    delete[] M1[i];
  for (int i = 0; i < n2; i++)
    delete[] M2[i];
  for (int i = 0; i < l; i++) {
    delete[] squareM1[i];
    delete[] squareM2[i];
    delete[] M5[i];
  }
  for (int i = 0; i < f; i++)
    delete[] M6[i];
  for (int i = 0; i < l / 2; i++) {
    delete[] mat1[i];
    delete[] mat2[i];
    delete[] mat3[i];
    delete[] mat4[i];
    delete[] mat5[i];
    delete[] mat6[i];
    delete[] mat7[i];
    delete[] mat8[i];
    delete[] mat9[i];
    delete[] mat10[i];
    delete[] mat11[i];
    delete[] mat12[i];
    delete[] p1[i];
    delete[] p2[i];
    delete[] p3[i];
    delete[] p4[i];
    delete[] p5[i];
    delete[] p6[i];
    delete[] p7[i];
  }
  delete[] M1, M2, squareM1, squareM2, M5, M6;
  delete[] mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12;
  delete[] p1, p2, p3, p4, p5, p6, p7;
}