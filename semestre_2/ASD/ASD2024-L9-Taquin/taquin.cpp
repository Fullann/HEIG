#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int N = 3; // Taille du taquin (3x3)

// Représentation d'un état du taquin
struct State {
    vector<int> board; // Plateau de jeu
    int zero_pos; // Position de la case vide (0)
    State(vector<int> b, int z) : board(b), zero_pos(z) {}
};

// Fonction de hash personnalisée pour std::vector<int>
struct vector_hash {
    size_t operator()(const vector<int>& v) const {
        hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

// Vérifie si l'état actuel est l'état but (0, 1, 2, 3, 4, 5, 6, 7, 8)
bool is_goal(const vector<int>& board) {
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] != i) return false;
    }
    return true;
}

// Génère les états voisins possibles en bougeant la case vide (0)
vector<State> get_neighbors(const State& state) {
    vector<State> neighbors;
    int x = state.zero_pos / N;
    int y = state.zero_pos % N;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto& d : directions) {
        int nx = x + d.first;
        int ny = y + d.second;
        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            vector<int> new_board = state.board;
            swap(new_board[state.zero_pos], new_board[nx * N + ny]);
            neighbors.push_back(State(new_board, nx * N + ny));
        }
    }
    return neighbors;
}

// Implémentation de l'algorithme BFS pour trouver le chemin le plus court
vector<int> bfs(const vector<int>& start) {
    queue<State> q;
    unordered_map<vector<int>, vector<int>, vector_hash> parent_map;
    int zero_pos = find(start.begin(), start.end(), 0) - start.begin();
    State initial_state(start, zero_pos);
    q.push(initial_state);
    parent_map[start] = {};

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (is_goal(current.board)) {
            vector<int> path;
            vector<int> board = current.board;
            while (parent_map[board].size() > 0) {
                path.push_back(current.zero_pos);
                board = parent_map[board];
                current.zero_pos = find(board.begin(), board.end(), 0) - board.begin();
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : get_neighbors(current)) {
            if (parent_map.find(neighbor.board) == parent_map.end()) {
                parent_map[neighbor.board] = current.board;
                q.push(neighbor);
            }
        }
    }
    return {};
}

int main() {
    // Entrée initiale du taquin
    vector<int> start = {0,1, 2, 3, 4, 5, 6, 7, 8};
    // Lecture de l'entrée utilisateur
    cout << "Entrez la configuration initiale du taquin (9 entiers de 0 à 8): ";
    for (int i = 0; i < 9; ++i) {
        cin >> start[i];
    }

    // Exécution de l'algorithme BFS
    vector<int> result = bfs(start);

    // Affichage du résultat
    if (!result.empty()) {
        cout << "Solution trouvée ! Mouvements de la case vide (0) : ";
        for (int pos : result) {
            cout << pos << " ";
        }
        cout << endl;
    } else {
        cout << "Aucune solution trouvée." << endl;
    }
    return 0;
}
