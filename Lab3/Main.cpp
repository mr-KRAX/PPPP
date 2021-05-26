#include <algorithm>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

constexpr auto SIZE = 16;

const std::string points[SIZE] = {"msk_AP", "msk_TS", "msk_WH", "mzh_TS",
                                  "mzh_WH", "zvn_WH", "NN_AP", "NN_TS", "NN_WH", "dzr_TS", "dzr_WH",
                                  "vlg_AP", "vlg_TS", "vlg_WH", "kam_TS", "kam_WH"};

const std::map<std::string, int> towns = {
    {"Moscow", 2},
    {"Mozhaisk", 4},
    {"Zvenigorod", 5},
    {"Nizhniy Novgorod", 8},
    {"Dzerzhinsk", 10},
    {"Volgograd", 13},
    {"Kamishin", 15}};

const std::map<std::string, int> table = {
    {"msk", 0},
    {"mzh", 1},
    {"zvn", 2},
    {"NN", 3},
    {"dzr", 4},
    {"vlg", 5},
    {"kam", 6}};

const std::tuple<int, int, double> tableCost[21] = {
    {500, 300, 100},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {0, 0, 0},
    {100, 60, 50},
    {500, 300, 100},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {200, 100, 500},
    {100, 60, 50},
    {500, 300, 100},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {200, 100, 500},
    {100, 60, 50}};

const int matrixDist[SIZE][SIZE] = {
    {0, 20, 30, 108, 110, 65, 398, 0, 0, 0, 0, 926, 0, 0, 0, 0},
    {20, 0, 10, 98, 100, 55, 0, 415, 0, 483, 0, 0, 937, 0, 1204, 0},
    {30, 10, 0, 108, 110, 65, 0, 0, 430, 0, 390, 0, 0, 652, 0, 1234},
    {108, 98, 108, 0, 5, 0, 0, 0, 0, 581, 0, 0, 1035, 0, 1302, 0},
    {110, 100, 110, 5, 0, 78, 0, 0, 540, 0, 500, 0, 0, 1062, 0, 1344},
    {65, 55, 65, 0, 78, 0, 0, 0, 495, 0, 455, 0, 0, 1017, 0, 1299},
    {398, 0, 0, 0, 0, 0, 0, 19, 23, 0, 26, 828, 0, 0, 0, 0},
    {0, 415, 0, 0, 0, 0, 19, 0, 4, 32, 0, 0, 840, 0, 919, 0},
    {0, 0, 430, 0, 540, 495, 23, 4, 0, 0, 40, 0, 0, 849, 0, 1010},
    {0, 483, 0, 581, 0, 0, 0, 32, 0, 0, 4, 0, 872, 0, 951, 0},
    {0, 0, 390, 0, 500, 455, 26, 0, 40, 4, 0, 0, 0, 889, 0, 1050},
    {926, 0, 0, 0, 0, 0, 828, 0, 0, 0, 0, 0, 15, 16, 0, 285},
    {0, 937, 0, 1035, 0, 0, 0, 840, 0, 872, 0, 15, 0, 2, 257, 281},
    {0, 0, 952, 0, 1062, 1017, 0, 0, 849, 0, 889, 16, 2, 0, 0, 282},
    {0, 1204, 0, 1302, 0, 0, 0, 919, 0, 951, 0, 0, 257, 0, 0, 2},
    {0, 0, 1234, 0, 1344, 1299, 0, 0, 1010, 0, 1050, 285, 281, 282, 2, 0}};

enum Type { Turbo,
            Standart,
            Economy };

// Наследование (ооооoчень отдаленный Strategy)
class Vehicle {
  protected:
  int speed;
  int volume;
  double price;
  int distance;

  public:
  Vehicle() {
    this->distance = 0;
  }

  Vehicle(std::tuple<int, int, double> tuple, int dist) {
    this->price = std::get<0>(tuple);
    this->speed = std::get<1>(tuple);
    this->volume = std::get<2>(tuple);
    this->distance = dist;
  }

  ~Vehicle() {
  }

  double sumCost(int mass) {
    return sumCost(mass, this->distance);
  }

  double sumCost(int mass, int dist) {
    return (mass / volume) * sumTime(dist) * price;
  }

  double sumTime(int dist) {
    return (double)dist / speed;
  }

  int getDistance() {
    return this->distance;
  }
};

class Plane : public Vehicle {
  public:
  Plane() : Vehicle() {
    this->price = 500;
    this->speed = 300;
    this->volume = 100;
  }

  Plane(std::tuple<int, int, double> tuple, int dist) : Vehicle(tuple, dist) {}
};

class Train : public Vehicle {
  public:
  Train() : Vehicle() {
    this->price = 200;
    this->speed = 100;
    this->volume = 500;
  }

  Train(std::tuple<int, int, double> tuple, int dist) : Vehicle(tuple, dist) {}
};

class Car : public Vehicle {
  public:
  Car() : Vehicle() {
    this->price = 100;
    this->speed = 60;
    this->volume = 50;
  }
  Car(std::tuple<int, int, double> tuple, int dist) : Vehicle(tuple, dist) {}
};

// Composit
class Track {
  int volume;
  vector<Vehicle *> vehicles;

  public:
  Track() {
    this->volume = 0;
  }

  Track(int volume) {
    this->volume = volume;
  }

  Track::~Track() {
    for(auto v : vehicles)
      delete v;
  }

  double getCost() {
    double cost = 0;
    for (auto v : vehicles)
      cost += v->sumCost(volume);
    return cost;
  }

  void addVehicle(Vehicle *v) {
    vehicles.push_back(v);
  }
};

class Order {
  string startPoint;
  string finishPoint;
  Track track;
  int volume;
  enum::Type type;

  public:
  double getCost() {
    return track.getCost();
  }

  Order::Order(Type deliv, std::string startP, std::string finishP, int vol) {
    this->startPoint = startP;
    this->finishPoint = finishP;
    this->type = deliv;
    this->track = best(startP, finishP, deliv, vol);
    this->volume = vol;
  }

  private:
  Car *NewCar(string point, int distance) {
    Car *car = nullptr;
    auto it = table.find(point.substr(0, point.find("_")));
    if (it != table.end()) {
      auto cost = tableCost[it->second * 3 + 2];
      car = new Car(cost, distance);
    }
    return car;
  }

  Train *NewTrain(string point, int distance) {
    Train *train = nullptr;
    auto it = table.find(point.substr(0, point.find("_")));
    if (it != table.end() && point.find("TS")) {
      auto cost = tableCost[it->second * 3 + 1];
      train = new Train(cost, distance);
    }
    return train;
  }

  Plane *NewPlane(string point, int distance) {
    Plane *plane = nullptr;
    auto it = table.find(point.substr(0, point.find("_")));
    if (it != table.end() && point.find("AP")) {
      auto cost = tableCost[it->second * 3];
      plane = new Plane(cost, distance);
    }
    return plane;
  }

  int **matrixUpd(Type type) {
    int **matrix = new int *[SIZE];
    for (int i = 0; i < SIZE; i++) {
      matrix[i] = new int[SIZE];
      for (int j = 0; j < SIZE; j++)
        matrix[i][j] = matrixDist[i][j];
    }
    switch (type) {
    case Economy:
      for (int i = 0; i < SIZE; i++) {
        if (points[i].find("TS"))
          for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 99999;
      }
    case Standart:
      for (int i = 0; i < SIZE; i++) {
        if (points[i].find("AP"))
          for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 99999;
      }
    case Turbo:
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
          if (matrix[i][j] == 0)
            matrix[i][j] = 99999;
      }
    }
    return matrix;
  }

  int *Order::optim(int **arr, int beginPoint, int endPoint) {
    int *d = new int[SIZE];
    int *v = new int[SIZE];
    int temp, minindex, min;
    int begin_index = beginPoint;

    for (int i = 0; i < SIZE; i++) {
      d[i] = 99999;
      v[i] = 1;
    }
    d[begin_index] = 0;

    do {
      minindex = 99999;
      min = 99999;
      for (int i = 0; i < SIZE; i++) {
        if ((v[i] == 1) && (d[i] < min)) {
          min = d[i];
          minindex = i;
        }
      }

      if (minindex != 99999) {
        for (int i = 0; i < SIZE; i++) {
          if (arr[minindex][i] > 0) {
            temp = min + arr[minindex][i];
            if (temp < d[i]) {
              d[i] = temp;
            }
          }
        }
        v[minindex] = 0;
      }
    } while (minindex < 99999);

    int *ver = new int[SIZE];
    int end = endPoint;
    ver[0] = end;
    int k = 1;
    int weight = d[end];

    while (end != begin_index) {
      for (int i = 0; i < SIZE; i++)
        if (arr[end][i] != 0) {
          int temp = weight - arr[end][i];
          if (temp == d[i]) {
            weight = temp;
            end = i;
            ver[k] = i + 1;
            k++;
          }
        }
    }
    for (int i = 0; i < k / 2; i++)
      std::swap(ver[i], ver[k - 1 - i]);
    delete[] d, v;
    return ver;
  }

  int decr(std::string str) {
    auto it = towns.find(str);
    if (it == towns.end())
      return -1;
    return it->second;
  }

  Track best(std::string startP, std::string finishP, Type deliv, int volume) {
    int start = decr(startP);
    int finish = decr(finishP);
    int **mat = matrixUpd(deliv);
    int *path = optim(mat, start, finish);
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
      if (path[i] == -1)
        break;
      count++;
    }
    Track track = Track(volume);
    Car *car1 = nullptr;
    Car *car2 = nullptr;
    Car *car3 = nullptr;
    Car *car4 = nullptr;
    Train *train1 = nullptr;
    Train *train2 = nullptr;
    Plane *plane1 = nullptr;

    switch (count) {
    case 7: {
      car4 = NewCar(points[path[6]], matrixDist[path[6]][path[7]]);
      track.addVehicle(car4 ? car4 : new Car());

      train1 = NewTrain(points[path[1]], matrixDist[path[1]][path[2]]);
      track.addVehicle(train1 ? train1 : new Train());

      train2 = NewTrain(points[path[5]], matrixDist[path[5]][path[6]]);
      track.addVehicle(train2 ? train2 : new Train());

      plane1 = NewPlane(points[path[3]], matrixDist[path[3]][path[4]]);
      track.addVehicle(plane1 ? plane1 : new Plane());

      /* falls through*/
    }
    case 5: {
      car3 = NewCar(points[path[4]], matrixDist[path[4]][path[5]]);
      track.addVehicle(car3 ? car3 : new Car());

      if (count == 5) {
        plane1 = NewPlane(points[path[3]], matrixDist[path[3]][path[4]]);
        track.addVehicle(train1 ? train1 : new Train());

        train1 = NewTrain(points[path[3]], matrixDist[path[3]][path[4]]);
        track.addVehicle(plane1 ? plane1 : new Plane());
      }
      /* falls through */
    }
    case 3: {
      car2 = NewCar(points[path[2]], matrixDist[path[2]][path[3]]);
      track.addVehicle(car2 ? car2 : new Car());

      if (count = 3) {
        plane1 = NewPlane(points[path[1]], matrixDist[path[1]][path[2]]);
        train1 = NewTrain(points[path[1]], matrixDist[path[1]][path[2]]);
        if (!train1)
          train1 = new Train();
        track.addVehicle(plane1 ? (Vehicle *)plane1 : (Vehicle *)train1);
      }
      /* falls through */
    }
    case 1: {
      car1 = NewCar(points[path[0]], matrixDist[path[0]][path[1]]);
      track.addVehicle(car1 ? car1 : new Car());
    }
    }
    return track;
  }
};

int main() {
  // Car c()
}