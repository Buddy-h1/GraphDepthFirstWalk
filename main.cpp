#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Graph {
public:
	Graph() {
		size = 0;
		firstNode = Node(size);
	}

	int size;

	class Node {
	public:
		Node() {}
		Node(int num) {
			for (auto i : nextNodes) { i = nullptr; }
			number = num + 1;
		}

		void pushNext(Node* next) {
			if (countNextNodes == 5) { return; }
			this->nextNodes[countNextNodes] = next;
			countNextNodes++;
		}

		int number;

		Node* nextNodes[5];
		int countNextNodes = 0;
	};

	void readFromFile(string& path) {
		ifstream file;
		file.open(path);

		//�������� �����
		if (!file.is_open()) { //���� ���� �� ��������
			cout << endl << "���� ���������� �������!" << endl;
			return;
		}
		else { //���� ���� ��������
			int countNode;
			file >> countNode;
			size = countNode;

			//�������� ������� ����������
			int** matrix = new int* [countNode];
			for (int i = 0; i < countNode; ++i) {
				matrix[i] = new int[countNode];
			}

			LinkMatrix = matrix;

			for (int i = 0; i < size; ++i) {
				visited[i] = false;
			}

			//������ �������� ���������� �� �����
			for (int i = 0; i < countNode; ++i) {
				for (int j = 0; j < countNode; ++j) {
					file >> matrix[i][j];
					file.ignore(1);
				}
			}

			file.close();

			//���������� ������� ����� ���������
			allNodes.clear();
			for (int i = 0; i < countNode; ++i) {
				Node* temp = new Node(i);
				allNodes.insert(make_pair(temp->number, temp));
			}

			//���������� ����� �� �������
			for (int i = 0; i < countNode; ++i) {
				for (int j = 0; j < countNode; ++j) {
					if (matrix[i][j] == 1) {
						allNodes[i + 1]->pushNext(allNodes[j + 1]);
					}
				}
				for (int j = 0; j < 5; j++) {
					allNodes[i + 1]->pushNext(nullptr);
				}
			}
		}
	}

	void Print() {
		for (auto i : allNodes) {
			cout << "V" << i.first << ": ";
			for (int j = 0; j < 5; ++j) {
				if (i.second->nextNodes[j] != nullptr) {
					cout << i.second->nextNodes[j]->number << " ";
				}
			}
			cout << endl;
		}
	}

	int** LinkMatrix;
	bool* visited = new bool[size]();
	void DFS(int start) {
		for (int i = 0; i < size; ++i) {
			visited[i] = false;
		}
		DFS_A(start);
	}
	void DFS_A(int start) {
		cout << start + 1 << " ";
		visited[start] = true;
		for (int i = 0; i < size; ++i) {
			if ((LinkMatrix[start][i] != 0) && (visited[i] == false)) {
				DFS_A(i);
			}
		}
	}

	Node firstNode;
	map<int, Node*> allNodes;
};

void PrintMenu() {
	cout << endl << "�������� �������:" << endl;
	cout << "[1] - ������� ���� �� ������� ���������� �� �����" << endl;
	cout << "[2] - ����� �����" << endl;
	cout << "[3] - ����������� ������� ������" << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Graph graph;

	string path = "C:\\Users\\buddy\\source\\repos\\adjacency table graph (depth-first walk)\\file.txt";


	setlocale(LC_ALL, "Russian");

	int command = 0;
	PrintMenu();
	while (cin >> command) {
		if (command == 1) {
			graph.readFromFile(path);
		}
		else if (command == 2) {
			graph.Print();
		}
		else if (command == 3) {
			int vertex;
			cout << "������ � �������: ";
			cin >> vertex;
			cout << endl;
			graph.DFS(vertex - 1);
			cout << endl;
		}
		else { cout << endl << "����������� �������!" << endl; }
		PrintMenu();
	}
	return 0;
}