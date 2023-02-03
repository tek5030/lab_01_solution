#include "Eigen/Eigen"
#include "opencv2/core/eigen.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

// You can use this definition of pi:
constexpr double pi = 3.14159265358979323846;

// You can convert from degrees to radians with this function:
constexpr double deg2rad(const double& deg)
{
  return deg * (pi/180.0);
}


int main()
{
  // 1. Eigen and homogeneous representations.
  //------------------------------------------
  // Translation.
  Eigen::Vector2d t{100, 200};

  // Rotation (take a look at https://eigen.tuxfamily.org/dox/group__Geometry__Module.html).
  const double angle_deg{30.0};
  Eigen::Matrix2d R = Eigen::Rotation2Dd(deg2rad(angle_deg)).toRotationMatrix();

  // Euclidean transformation that rotates and then translates.
  Eigen::Matrix3d E;
  E << R, t,
       0, 0, 1;

  std::cout << "Euclidean transformation E = " << std::endl << E << std::endl << std::endl;

  // Perform the transformation on a pixel u.
  Eigen::Vector2d u{100, 100};
  Eigen::Vector2d u_transformed = (E * u.homogeneous()).hnormalized();

  std::cout << "Original pixel u = " << std::endl << u << std::endl << std::endl;
  std::cout << "Transformed pixel u_transformed = " << std::endl << u_transformed << std::endl << std::endl;


  // 2. Eigen and OpenCV.
  //---------------------
  cv::Mat E_cv;

  // Convert from Eigen matrix to OpenCV cv::Mat.
  cv::eigen2cv(E, E_cv);

  std::cout << "Euclidean transformation E_cv = " << std::endl << E_cv << std::endl << std::endl;


  // 3. Transform images.
  //---------------------
  // Read the image.
  cv::Mat img_orig = cv::imread("img_grid.png");
  if (img_orig.empty())
  {
    std::cerr << "Could not find image file" << std::endl;
    return EXIT_FAILURE;
  }

  // Display the original image.
  std::string orig_win_title{"Lab 1.2: Original image"};
  cv::namedWindow(orig_win_title, cv::WINDOW_NORMAL);
  cv::imshow(orig_win_title, img_orig);

  // Perform transformation on the image.
  cv::Mat img_trans_E;
  cv::warpPerspective(img_orig, img_trans_E, E_cv, img_orig.size(), cv::INTER_CUBIC);

  // Display the transformed image.
  std::string trans_win_title{"Lab 1.2: Transformed image"};
  cv::namedWindow(trans_win_title, cv::WINDOW_NORMAL);
  cv::imshow(trans_win_title, img_trans_E);


  // 4. Composing transformations.
  //------------------------------
  // Compose transformations to rotate and scale around the centre of the image.
  // First, find the pixel position of the image centre.
  Eigen::Vector2d c{0.5*img_orig.cols, 0.5*img_orig.rows};

  // Define the translation that moves the origin to the image centre.
  Eigen::Matrix3d E_translate_to_centre{Eigen::Matrix3d::Identity()};
  E_translate_to_centre.col(2).head<2>() = -c;

  // Use the same rotation as in 1.
  Eigen::Matrix3d E_rotate{Eigen::Matrix3d::Identity()};
  E_rotate.topLeftCorner<2,2>() = R;

  // Define a scaling.
  const double scale = 0.75;
  Eigen::Matrix3d S_scale{Eigen::Matrix3d::Identity()};
  S_scale.topLeftCorner<2,2>() *= scale;

  // Define the translation that moves the origin back.
  Eigen::Matrix3d E_translate_back{Eigen::Matrix3d::Identity()};
  E_translate_back.col(2).head<2>() = c;

  // Compose the transformations to find the resulting similarity transform.
  Eigen::Matrix3d S = E_translate_back * S_scale * E_rotate * E_translate_to_centre;

  // Perform the transformation on the image.
  cv::Mat S_cv;
  cv::eigen2cv(S, S_cv);

  cv::Mat img_trans_S;
  cv::warpPerspective(img_orig, img_trans_S, S_cv, img_orig.size(), cv::INTER_CUBIC);

  std::string composed_win_title{"Lab 1.2: Composed transformation"};
  cv::namedWindow(composed_win_title, cv::WINDOW_NORMAL);
  cv::imshow(composed_win_title, img_trans_S);

  // Please press a key, don't close the windows with your mouse.
  cv::waitKey();
  return EXIT_SUCCESS;
}
