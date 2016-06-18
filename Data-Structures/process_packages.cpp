#include <iostream>
#include <queue>
#include <vector>

struct Segment {
    Segment(int arrival_time, int end_time):
        arrival_time(arrival_time),
        end_time(end_time)
    {}

    int arrival_time;
    int end_time;
};

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped; // boolean value whether it is dropped
    int start_time; // time it starts to get processed
};

class Buffer {
public:
    Buffer(int size):
        size_(size), // constructor to initialize the size of the buffer
		last_arrival(0),
        finish_time_() // default constructor to initialize the deque
    {}

    Response Process(const Request &request) {
        // write your code here
		if(finish_time_.empty()){
			finish_time_.push(request.process_time);
			return Response(false,request.arrival_time);
		}
		
		if(finish_time_.size() == size_){
			// current start time is the max between arrival time and the end time of the most recent addition
			int start_time = std::max(request.arrival_time,finish_time_.back());
			int finish_time = start_time + request.process_time; // start time plus process time
			
			if(request.arrival_time - finish_time_.front() >= 0){
				finish_time_.pop();
				finish_time_.push(finish_time);
				return Response(false,start_time);
			}
			
			return Response(true,-1); // when the diff case isn't satisfied
		}
		
		int start_time = std::max(request.arrival_time,finish_time_.back());
		int finish_time = start_time + request.process_time; // start time plus process time
		
		finish_time_.push(finish_time);
		
		return Response(false,start_time);
    }
private:
    int size_;
	// each finish_time at i, contains arrival_time and end_time
	int last_arrival;
    std::queue <int> finish_time_; //  maybe should use deque instead?
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses; // maybe better to return std::vetor from buffer process
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
