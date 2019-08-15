#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <chrono>
#include <numeric>
#include <fstream>

using namespace ur_rtde;
using namespace std;
double s;
double t;
std::vector<double> qact;
/*void copyVecFast(const vec<double> &original)
{
  vector<double> qact;
  qact.reserve(original.size());
  copy(original.begin(), original.end(), back_inserter(qact));
}*/
int main(int argc, char *argv[])
{
  RTDEReceiveInterface rtde_receive("192.168.1.100");  // opening an RTDE network connection
  remove("ur10data.csv");                              // Deleting the temporary log file
  ofstream rbtdata;                                    // Initialising a log file
  rbtdata.open("ur10data.csv");                        // Opening a log file
 
  while (1)
  {
  
      cout << "Timestamp " << endl;  // Time of execution of the script
      s = rtde_receive.getTimestamp();
      cout << s << " ";
      cout.precision(8);
      rbtdata.precision(8);
      // rbtdata << "Timestamp";
      rbtdata << s << ", ";
	  
      std::vector<double> actual_q = rtde_receive.getActualQ();  // Get actual joint positions
      // rbtdata << "Actual q is: " << endl;
      for (size_t i = 0; i < actual_q.size() - 1; i++)
      {
        cout << "Actual q is: " << endl;
        cout << actual_q[i] << endl;
        rbtdata << actual_q[i] << ", ";
      }
      rbtdata << actual_q[actual_q.size() - 1] << std::endl;
      std::vector<double> actual_qd = rtde_receive.getActualQd();  // Get actual joint velocities
      // rbtdata << "Actual qd is: " << endl;
      for (size_t i = 0; i < actual_qd.size()-1; i++)
      {
        cout << "Actual qd is: " << endl;

        rbtdata << actual_qd[i] << ", ";
      }
      rbtdata << actual_qd[actual_qd.size()-1] << std::endl;
    }
    /* std::vector<double> actual_TCP = rtde_receive.getActualTCPPose();  // Get actual TCP pose
     for (size_t i = 0; i < actual_TCP.size() - 1; i++)
     {
       {
         cout << "Actual TCP Pose is: " << endl;

         rbtdata << actual_TCP[i] << ", ";
       }
       rbtdata << actual_TCP[actual_TCP.size() - 1] << std::endl;
     }*/
     rbtdata.flush();
     rbtdata.close();
     cout << endl;
     return 0;
  }

