#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using i128 = __int128_t;

// Быстрое возведение в степень по модулю: вычисляет a^e mod mod безопасно, используя 128-битные промежуточные значения
ull modexp(ull a, ull e, ull mod) {
	i128 result = 1;
	i128 base = a % mod;
	while (e) {
		if (e & 1) result = (result * base) % mod;
		base = (base * base) % mod;
		e >>= 1;
	}
	return (ull)result;
}

// Расширенный алгоритм Евклида: возвращает gcd(a,b) и находит x,y такие что ax+by=g
long long egcd(long long a, long long b, long long &x, long long &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	long long x1, y1;
	long long g = egcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}

// Модульная обратная: обратный элемент a по модулю m. Возвращает 0, если обратного не существует.
ull modinv(ull a, ull m) {
	long long x, y;
	long long g = egcd((long long)a, (long long)m, x, y);
	if (g != 1) return 0;
	long long res = x % (long long)m;
	if (res < 0) res += m;
	return (ull)res;
}

// Небольшой встроенный список простых чисел (для обучения/демо). Значения > 1000, чтобы одиночный байт помещался в n.
static const vector<ull> PRIME_POOL = {
	1009ULL,1013ULL,1019ULL,1021ULL,1031ULL,1033ULL,1039ULL,1049ULL,1051ULL,1061ULL,
	1063ULL,1069ULL,1087ULL,1091ULL,1093ULL,1097ULL,1103ULL,1109ULL,1117ULL,1123ULL,
	1129ULL,1151ULL,1153ULL,1163ULL,1171ULL,1181ULL,1187ULL,1193ULL,1201ULL,1213ULL,
	1217ULL,1223ULL,1229ULL,1231ULL,1237ULL,1249ULL,1259ULL,1277ULL,1279ULL,1283ULL,
	1289ULL,1291ULL,1297ULL,1301ULL,1303ULL,1307ULL,1319ULL,1321ULL,1327ULL,1361ULL,
	1367ULL,1373ULL,1381ULL,1399ULL,1409ULL,1423ULL,1427ULL,1429ULL,1433ULL,1439ULL,
	1447ULL,1451ULL,1453ULL,1459ULL,1471ULL,1481ULL,1483ULL,1487ULL,1489ULL,1493ULL,1499ULL
};

void usage(const char *prog) {
	cerr << "Использование:\n";
	cerr << "  " << prog << " genkeys [seed]       # сгенерировать p,q,n,e,d и вывести их\n";
	cerr << "  " << prog << " encrypt <n> <e> <message...>   # зашифровать сообщение и вывести числа, разделённые пробелом\n";
	cerr << "  " << prog << " decrypt <n> <d> <c1 c2 ...>   # расшифровать числа и вывести исходный текст\n";
}

int cmd_genkeys(unsigned seed) {
	mt19937_64 rng(seed);
	uniform_int_distribution<size_t> dist(0, PRIME_POOL.size()-1);
	ull p = PRIME_POOL[dist(rng)];
	ull q = PRIME_POOL[dist(rng)];
	while (q == p) q = PRIME_POOL[dist(rng)];

	ull n = p * q;
	ull phi = (p - 1) * (q - 1);

	ull e = 65537ULL;
	if (std::gcd(e, phi) != 1) {
		// запасной вариант: найти небольшое нечетное e
		for (ull cand = 3; cand < phi; cand += 2) {
			if (std::gcd(cand, phi) == 1) { e = cand; break; }
		}
	}
	ull d = modinv(e, phi);
	if (d == 0) {
		cerr << "Не удалось вычислить модульную обратную для выбранного e.\n";
		return 1;
	}

	// Печать ключей в удобном для парсинга формате
	cout << "p=" << p << "\n";
	cout << "q=" << q << "\n";
	cout << "n=" << n << "\n";
	cout << "e=" << e << "\n";
	cout << "d=" << d << "\n";
	return 0;
}

int cmd_encrypt(ull n, ull e, const string &message) {
	// шифруем каждый байт как отдельный блок сообщения
	vector<ull> ciphertext;
	for (unsigned char ch : message) {
		ull m = (ull)ch;
		if (m >= n) {
			cerr << "Значение байта сообщения >= n; выберите большие простые.\n";
			return 2;
		}
		ull c = modexp(m, e, n);
		ciphertext.push_back(c);
	}

	// печать через пробел
	for (size_t i = 0; i < ciphertext.size(); ++i) {
		if (i) cout << ' ';
		cout << ciphertext[i];
	}
	cout << '\n';
	return 0;
}

int cmd_decrypt(ull n, ull d, const vector<ull> &cipher) {
	string out;
	out.reserve(cipher.size());
	for (ull c : cipher) {
		ull m = modexp(c, d, n);
		if (m > 255) {
			cerr << "Дешифрованный блок >255, невозможно преобразовать в один байт.\n";
			return 3;
		}
		out.push_back((char)m);
	}
	cout << out << '\n';
	return 0;
}

// Компоновка: включаем main только если определён RSA_STANDALONE
#ifdef RSA_STANDALONE
int main(int argc, char **argv) {
	if (argc < 2) { usage(argv[0]); return 1; }
	string cmd = argv[1];
	if (cmd == "genkeys") {
		unsigned seed = (unsigned)chrono::high_resolution_clock::now().time_since_epoch().count();
		if (argc >= 3) seed = (unsigned)stoul(argv[2]);
		return cmd_genkeys(seed);
	} else if (cmd == "encrypt") {
		if (argc < 5) { usage(argv[0]); return 1; }
		ull n = stoull(argv[2]);
		ull e = stoull(argv[3]);
		// объединяем оставшиеся аргументы в сообщение (позволяет пробелы)
		string msg;
		for (int i = 4; i < argc; ++i) {
			if (i > 4) msg.push_back(' ');
			msg += argv[i];
		}
		return cmd_encrypt(n, e, msg);
	} else if (cmd == "decrypt") {
		if (argc < 5) { usage(argv[0]); return 1; }
		ull n = stoull(argv[2]);
		ull d = stoull(argv[3]);
		// объединяем оставшиеся аргументы в строку и парсим числа
		vector<ull> cipher;
		for (int i = 4; i < argc; ++i) {
			// argv[i] может содержать несколько чисел, разделённых пробелами, если аргумент в кавычках; обычно числа передаются раздельно
			string token = argv[i];
			// пробуем распарсить токен по пробелам/запятым при необходимости
			stringstream ss(token);
			ull x;
			while (ss >> x) cipher.push_back(x);
		}
		return cmd_decrypt(n, d, cipher);
	} else {
		usage(argv[0]);
		return 1;
	}
}
#endif // RSA_STANDALONE
