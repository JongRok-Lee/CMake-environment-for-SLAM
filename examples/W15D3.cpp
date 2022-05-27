#include <iostream>
#include "module.hpp"
#include <chrono>
#include <thread>

// path to trajectory file (Global variable)
std::string trajectory_file = std::string(PROJECT_DIR) + "/trajectory.txt";

void DrawTrajectory(std::vector<Eigen::Isometry3d>);

int main(int argc, char **argv) {

    // Eigen::Isometry3d means 4 by 4 SE(3) Matrix. -> poses : vector<Transform Matrix>
    std::vector<Eigen::Isometry3d> poses;

    // std::ifstream allows us to read TXT file
    std::ifstream fin(trajectory_file);

    // If we cannot read the trajectory file, the process is interrupted.
    if (!fin) {
        std::cout << "cannot find trajectory file at " << trajectory_file << std::endl;
        return 1;
    }

    // The contents of the trajectory file are time, location, and orientation information.
    // Type of the orientation information is Quaternions (qx, qy, qz, qw).
    // 
    double time, tx, ty, tz, qx, qy, qz, qw;
    while (!fin.eof()) {
        
        fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;

        // qx, qy, qz, qw -> Quaternions -> R of SE(3)
        Eigen::Isometry3d Twr(Eigen::Quaterniond(qw, qx, qy, qz));

        // Twr -> R|t of SE(3)
        Twr.pretranslate(Eigen::Vector3d(tx, ty, tz));
        
        // Store the Twr
        poses.push_back(Twr);
    }
  
    std::cout << "read total " << poses.size() << " pose entries" << std::endl;

    // draw trajectory in pangolin
    DrawTrajectory(poses);
    
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(std::vector<Eigen::Isometry3d> poses) {
  // create pangolin window and plot the trajectory
  pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  pangolin::OpenGlRenderState s_cam(
    pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
    pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
  );

  pangolin::View &d_cam = pangolin::CreateDisplay()
    .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
    .SetHandler(new pangolin::Handler3D(s_cam));

  while (pangolin::ShouldQuit() == false) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d_cam.Activate(s_cam);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2);
    for (size_t i = 0; i < poses.size(); i++) {
      
      Eigen::Vector3d Ow = poses[i].translation();
      Eigen::Vector3d Xw = poses[i] * (0.1 * Eigen::Vector3d(1, 0, 0));
      Eigen::Vector3d Yw = poses[i] * (0.1 * Eigen::Vector3d(0, 1, 0));
      Eigen::Vector3d Zw = poses[i] * (0.1 * Eigen::Vector3d(0, 0, 1));
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Xw[0], Xw[1], Xw[2]);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Yw[0], Yw[1], Yw[2]);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Zw[0], Zw[1], Zw[2]);
      glEnd();
    }
    
    for (size_t i = 0; i < poses.size() - 1; i++) {
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      auto p1 = poses[i], p2 = poses[i + 1];
      glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
      glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
      glEnd();
    }
    pangolin::FinishFrame();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));   // sleep 5 ms
  }
}