#include <bits/stdc++.h> 

using namespace std; 

struct Point { 
	int x;
    int y; 
}; 

bool compare_x(Point p1, Point p2) { 
 	return (p1.x < p2.x); 
} 

bool compare_y(Point p1, Point p2)  { 
	return (p1.y < p2.y); 
} 


double find_dist(Point p1, Point p2) { 
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) ); 
} 

double find_strip_min_distance(Point points[], int points_count, double min_dist) { 
	double mn = min_dist; 

	sort(points, points+points_count, compare_y); 
 
	for (int i = 0; i < points_count; i++) { 
		for (int j = i+1; j < points_count && (points[j].y-points[i].y) < mn; j++) {
			double dist = find_dist(points[i], points[j]);
            if (dist < mn) { 
				mn = dist; 
            }
        }
    }

	return mn; 
} 

double find_minimum_distance(Point points[], int points_count) { 
	if (points_count <= 3) {
	    double mn = DBL_MAX; 
	
        for (int i = 0; i < points_count; i++) { 
            for (int j = i+1; j < points_count; j++) {
                double dist = find_dist(points[i], points[j]);
                if (dist < mn) {
                    mn = dist;
                }
            }
        } 

        return mn;
    }
	
    int mid = points_count / 2; 
	Point mid_point = points[mid]; 

	double min_dist_left = find_minimum_distance(points, mid); 
	double min_dist_right = find_minimum_distance(points + mid, points_count - mid); 

	double min_dist = min(min_dist_left, min_dist_right); 

	Point strip_points[points_count];
    int strip_points_count = 0; 
	for (int i = 0; i < points_count; i++) {
		if (abs(points[i].x - mid_point.x) < min_dist) { 
			strip_points[strip_points_count] = points[i], strip_points_count++;
        } 
    }

	return min(min_dist, find_strip_min_distance(strip_points, strip_points_count, min_dist)); 
} 

double find_ans(Point points[], int points_count) { 
	sort(points, points+points_count, compare_x); 
    
	return find_minimum_distance(points, points_count); 
} 

int main() { 
	int points_count;
    cout << "Enter points count:" << endl;
    cin >> points_count;

    Point points[points_count];
    
    cout << "Enter the coordinate of the points:" << endl;
    for (int i = 0; i < points_count; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = Point{x, y};
    } 
	
    cout << "The smallest distance is " << find_ans(points, points_count) << endl; 
	
    return 0; 
} 