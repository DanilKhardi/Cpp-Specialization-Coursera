#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <utility>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
	string operation_type;
	is >> operation_type;
	if (operation_type == "NEW_BUS") {
		string bus;
		is >> bus;
		int stop_count;
		is >> stop_count;
		vector<string> stops(stop_count);
		for (auto& stop : stops) {
			is >> stop;
		}
		q.type = QueryType::NewBus;
		q.bus = bus;
		q.stops = stops;
	} else if (operation_type == "BUSES_FOR_STOP") {
		string stop;
		is >> stop;
		q.type = QueryType::BusesForStop;
		q.stop = stop;
	} else if (operation_type == "STOPS_FOR_BUS") {
		string bus;
		is >> bus;
		q.type = QueryType::StopsForBus;
		q.bus = bus;
	} else if (operation_type == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
  return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру
	string stop;
	vector<string> buses_list;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
	if (r.buses_list.size() == 0) {
		os << "No stop";
	} else {
		bool is_first = true;
		for (const auto& bus : r.buses_list) {
			if (!is_first) {
				os << ' ';
		}
			is_first = false;
			os << bus;
	}
	}
  return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
	string bus;
	vector<pair<string, vector<string>>> stops_and_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
	if (r.stops_and_buses.size() == 0) {
		os << "No bus";
	} else {
		for (const auto& [stop, buses] : r.stops_and_buses) {
		os << "Stop " << stop << ": ";
		if (buses.size() == 1 ) {
			os << "no interchange" << endl;
		} else {
			bool is_true = true;
			for (const auto& bus : buses) {
				if (!is_true) {
					os << ' ';
				}
				is_true = false;
				if (bus != r.bus) {
					os << bus;
				}
			}
			os << endl;
		}
	}
	}

  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
	map<string, vector<string>> buses_info;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
	if (r.buses_info.size() == 0) {
		os << "No buses";
	} else {
		for (const auto& [bus, stops] : r.buses_info) {
			os << "Bus " << bus << ": ";
			bool is_first = true;
			for (const auto& stop : stops) {
				if (!is_first) {
					os << ' ';
				}
				is_first = false;
				os << stop;
			}
			os << endl;
		}
	}
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
	  buses_to_stops_[bus] = stops;
	  for (const auto& stop : stops) {
		  stops_to_buses_[stop].push_back(bus);
	  }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
	  BusesForStopResponse response;
	  response.stop = stop;
	  if (stops_to_buses_.count(stop) != 0) {
		  for (const auto& bus : stops_to_buses_.at(stop)) {
		  		  response.buses_list.push_back(bus);
		  	  }
	  }
	  return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
	  StopsForBusResponse response;
	  response.bus = bus;
	  if (buses_to_stops_.count(bus) != 0) {
		  for (const auto& stop : buses_to_stops_.at(bus)) {
			  response.stops_and_buses.push_back(make_pair(stop, stops_to_buses_.at(stop)));
	  }
	  }
	  return response;
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
	  AllBusesResponse response;
	  for (const auto& [bus, stops] : buses_to_stops_) {
		  response.buses_info[bus] = stops;
	  }
	  return response;
  }
private:
  map<string, vector<string>> buses_to_stops_, stops_to_buses_;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
