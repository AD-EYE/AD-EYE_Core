#ifndef SS_TRAJPLANNER_TRAJ_SET_HANDLER_H // keep this header file from being included multiple times
#define SS_TRAJPLANNER_TRAJ_SET_HANDLER_H

// csv handling
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class TrajectorySetHandler
{
public:
  TrajectorySetHandler() {}

  // trajset struct
  struct trajectory{
    std::vector<std::string> header;
    std::vector<float> t;
    std::vector<float> X;
    std::vector<float> Y;
    std::vector<float> psi;
    std::vector<float> v_x;
    std::vector<float> a_x;
    std::vector<float> beta;
    std::vector<float> kappa;
    std::vector<float> S_x;
    std::vector<float> beta_rate;
    std::vector<float> kappa_rate;
    std::vector<float> j_x;
    float valid;
    float v_init;
    float ID;
    float timeUntilStopped;
    float finalPsi;
    float j_max;
    float RSARmin;
    float RSARmax;
  };

  void setTrajToZero(trajectory & traj){
    for(size_t i = 0; i<traj.t.size(); i++){
      // traj.t is left as is
      traj.X.push_back(0);
      traj.Y.push_back(0);
      traj.psi.push_back(0);
      traj.v_x.push_back(0);
      traj.a_x.push_back(0);
      traj.beta.push_back(0);
      traj.kappa.push_back(0);
      traj.S_x.push_back(0);
      traj.beta_rate.push_back(0);
      traj.kappa_rate.push_back(0);
      traj.j_x.push_back(0);
    }
    traj.valid = true;
    traj.v_init = 0;
    traj.ID = 0;
    traj.timeUntilStopped = 0;
    traj.finalPsi = 0;
    traj.j_max = 0;
    traj.RSARmin = 0;
    traj.RSARmax = 0;
  }

  void load_trajectory_set(std::string filename, std::vector<std::vector<trajectory>> &trajSet, std::vector<float> &v_init_vector ){

    ROS_INFO_STREAM("Started reading trajset from file");

    // parsing variables
    std::string line;
    std::string element;
    float value;

    // trajectory set
    std::vector<trajectory> trajSubSet;

    // trajectory
    std::vector<std::string> header;
    std::vector<float> t;                   // state variables
    std::vector<float> X;
    std::vector<float> Y;
    std::vector<float> psi;
    std::vector<float> v_x;
    std::vector<float> a_x;
    std::vector<float> beta;
    std::vector<float> kappa;
    std::vector<float> S_x;
    std::vector<float> beta_rate;
    std::vector<float> kappa_rate;
    std::vector<float> j_x;

    float valid = 0;                           // trajectory parameters
    float v_init = 0;
    float ID = 0;
    float timeUntilStopped = 0;
    float finalPsi = 0;
    float j_max = 0;
    float RSARmin = 0;
    float RSARmax = 0;

    // other
    float last_v_init = 0;
    bool first_traj_has_been_set = false;

    // open file
    std::ifstream inputFile;
    inputFile.open (filename);

    if (!inputFile.is_open()){
      std::stringstream ss;
      ss << "ERROR: couldn't open file" << filename;
      throw std::runtime_error(ss.str());
    }
    else{
      while (inputFile.good()){

        // per trajectory:
        std::getline (inputFile,line);
        if(!line.empty()){
          if(line.at(0) == 't'){
            std::stringstream ss(line);
            while(ss.good()){
              getline( ss, element, ',' );
              if(!element.empty()){
                header.push_back(element);
              }
            }
          }
          else {
            std::stringstream ss(line);
            int i = 0;
            while(ss.good()){
              getline( ss, element, ',' );
              if(!element.empty()){
                value = strtof(element.c_str(),0); // string to float
                switch (i) {
                case 0:
                  t.push_back(value);
                  break;
                case 1:
                  X.push_back(value);
                  break;
                case 2:
                  Y.push_back(value);
                  break;
                case 3:
                  psi.push_back(value);
                  break;
                case 4:
                  v_x.push_back(value);
                  break;
                case 5:
                  a_x.push_back(value);
                  break;
                case 6:
                  kappa.push_back(value);
                  break;
                case 7:
                  kappa_rate.push_back(value);
                  break;
                case 8:
                  j_x.push_back(value);
                  break;
                case 9:
                  valid = value;
                  break;
                case 10:
                  v_init = value;
//                  if(!first_traj_has_been_set){
//                    last_v_init = v_init;
//                  }
                  break;
                case 11:
                  ID = value;
                  break;
                case 12:
                  beta.push_back(value);
                  break;
                case 13:
                  beta_rate.push_back(value);
                  break;
                case 14:
                  S_x.push_back(value);
                  break;
                case 15:
                  timeUntilStopped = value;
                  break;
                case 16:
                  finalPsi = value;
                  break;
                case 17:
                  j_max = value;
                case 18:
                  RSARmin = value;
                  break;
                case 19 :
                  RSARmax = value;
                  break;
                default:
                  ROS_INFO_STREAM("ERROR: unknown parsing case");
                  break;
                }
              }
              i++;
            }
          }
        } // end read line

        // fill vector of trajSubSets
        if((v_init != last_v_init) && first_traj_has_been_set){                                   /// Placed this if statement to the middle of the while from down below, because it did not work there
          trajSet.push_back(trajSubSet);
          v_init_vector.push_back(traj.v_init);             
          trajSubSet.clear();
        }
        last_v_init = v_init;

        // if new trajectory
        if(t.size() >= 100){ // check for 2x empty lines instead?
          traj.t = t;
          traj.X = X;
          traj.Y = Y;
          traj.psi = psi;
          traj.v_x = v_x;
          traj.a_x = a_x;
          traj.beta = beta;
          traj.kappa = kappa;
          traj.S_x = S_x;
          traj.beta_rate = beta_rate;
          traj.kappa_rate = kappa_rate;
          traj.j_x = j_x;
          traj.valid = valid;
          traj.v_init = v_init;
          traj.ID = ID;
          traj.timeUntilStopped = timeUntilStopped;
          traj.finalPsi = finalPsi;
          traj.j_max = j_max;
          traj.RSARmin = RSARmin;
          traj.RSARmax = RSARmin;

          // store traj in set
          trajSubSet.push_back(traj);
          first_traj_has_been_set = true;

          // clear all state variable vectors
          header.clear();
          t.clear();
          X.clear();
          Y.clear();
          psi.clear();
          v_x.clear();
          a_x.clear();
          beta.clear();
          kappa.clear();
          S_x.clear();
          beta_rate.clear();
          kappa_rate.clear();
          j_x.clear();
          // the floats will be overwritten anyway
        }
      }
      //trajSet.erase(trajSet.begin()); // hack
      trajSet.push_back(trajSubSet); // push back last trajSubset
      v_init_vector.push_back(traj.v_init);

      // end per trajectory
      inputFile.close();
    }

    ROS_INFO_STREAM("Finished Loading Trajectory Set");

  }


  void check_traj_set(std::vector<std::vector<trajectory>> &trajSet, std::vector<float> &v_init_vector){
    ROS_INFO_STREAM("trajSet info: ");
    ROS_INFO_STREAM("trajSet.size = " <<trajSet.size());
    for(auto const& trajSubSet: trajSet) {
      ROS_INFO_STREAM("trajSubSet.size = " <<trajSubSet.size());
    }
    ROS_INFO_STREAM("v_init_vector.size = " <<v_init_vector.size());
    for(auto const& v_init: v_init_vector) {
      ROS_INFO_STREAM("v_init = " <<v_init);
    }
  }

private:
  //std::vector<std::vector<trajectory> > trajSet;
  //std::vector<float> v_init_vector;
  trajectory traj;

};


#endif
