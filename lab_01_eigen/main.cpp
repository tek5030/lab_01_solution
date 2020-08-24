#include "Eigen/Eigen"
#include <iostream>

int main()
{
  // a) Create a few vectors and matrices.
  //--------------------------------------
  // Create vector t.
  Eigen::Vector3d t{1.0, 0.0, 3.0};

  // Create matrix A.
  Eigen::Matrix3d A;
  A << 1.0, 0.0, 3.0,
       4.0, 5.0, 6.0,
       7.0, 8.0, 9.0;

  // Create identity matrix I.
  Eigen::Matrix3d I{Eigen::Matrix3d::Identity()};

  // Create matrix T.
  Eigen::Matrix4d T;
  T << A, t,
       0, 0, 0, 1;

  // Create matrix B.
  Eigen::Matrix3d B{A.transpose()};

  // Print the results.
  std::cout << "a) Create a few vectors and matrices:" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "t = " << std::endl << t << std::endl << std::endl;
  std::cout << "A = " << std::endl << A << std::endl << std::endl;
  std::cout << "I = " << std::endl << I << std::endl << std::endl;
  std::cout << "T = " << std::endl << T << std::endl << std::endl;
  std::cout << "B = " << std::endl << B << std::endl << std::endl;


  // b) Coefficients.
  //-----------------
  // Set t_2.
  t(1) = 2.0;

  // Set A_12.
  A(0, 1) = 2.0;

  // Set the corresponding coefficients in T.
  T(0, 1) = 2.0;
  T(1, 3) = 2.0;

  // Print the results.
  std::cout << "b) Coefficients:" << std::endl;
  std::cout << "----------------" << std::endl;
  std::cout << "t = " << std::endl << t << std::endl << std::endl;
  std::cout << "A = " << std::endl << A << std::endl << std::endl;
  std::cout << "T = " << std::endl << T << std::endl << std::endl;


  // c) Block operations.
  //---------------------
  // Extract r_2.
  Eigen::RowVector3d r_2 = A.row(1);

  // Extract c_2.
  Eigen::Vector3d c_2 = A.col(1);

  // Extract T_3x4.
  using Matrix34d = Eigen::Matrix<double, 3, 4>; // Make an "alias" for this matrix type for convenience.
  Matrix34d T_3x4 = T.topLeftCorner<3,4>();

  // Print the results.
  std::cout << "c) Block operations:" << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << "r_2 = " << std::endl << r_2 << std::endl << std::endl;
  std::cout << "c_2 = " << std::endl << c_2 << std::endl << std::endl;
  std::cout << "T_3x4 = " << std::endl << T_3x4 << std::endl << std::endl;

  // Changing r_2, c_2 and T_3x4 will not alter A and T, since the extracted blocks are copies
  // (after they were converted from Eigen::Block<> to vectors/matrices).
  // To work on the same memory as in A and T, we can for example:
  // 1) Use block as lvalue:
  A.row(1).setZero();

  // 2) Use convenient typedefs for row or column expressions:
  Eigen::Matrix3d::ColXpr c_2_xpr = A.col(1);
  c_2_xpr.setZero();

  // 3) Use a Eigen::Ref<>:
  Eigen::Ref<Matrix34d> T_3x4_ref = T.topLeftCorner<3,4>();
  T_3x4_ref.setZero();

  // Print the results.
  std::cout << "After setting blocks to 0:" << std::endl;
  std::cout << "A = " << std::endl << A << std::endl << std::endl;
  std::cout << "T = " << std::endl << T << std::endl << std::endl;


  // d) Matrix and vector arithmetic.
  //---------------------------------
  // Print the results directly.
  std::cout << "d) Matrix and vector arithmetic:" << std::endl;
  std::cout << "--------------------------------" << std::endl;
  std::cout << "t + c_2 = " << std::endl << t + c_2 << std::endl << std::endl;
  std::cout << "A + I = " << std::endl << A + I << std::endl << std::endl;
  std::cout << "(A+I) * T_3x4 = " << std::endl << (A+I) * T_3x4 << std::endl << std::endl;
  std::cout << "t.transpose() * c_2 = " << std::endl << t.transpose() * c_2 << std::endl << std::endl;
  std::cout << "t.dot(c_2) = " << std::endl << t.dot(c_2) << std::endl << std::endl;
  std::cout << "Element-wise B * I = " << std::endl << B.cwiseProduct(I) << std::endl << std::endl;
  std::cout << "Element-wise (array) B * I = " << std::endl << B.array() * I.array() << std::endl << std::endl;

  // e) Reductions.
  //---------------
  // Print the results directly.
  std::cout << "e) Reductions:" << std::endl;
  std::cout << "--------------" << std::endl;
  std::cout << "Sum of elements in I = " << std::endl << I.sum() << std::endl << std::endl;

  Eigen::Matrix3d::Index min_row;
  Eigen::Matrix3d::Index min_col;
  std::cout << "Min in B = " <<  B.minCoeff(&min_row, &min_col);
  std::cout << " at (" << min_row << ", " << min_col << ")" << std::endl << std::endl;

  std::cout << "Max of each column in B = " << std::endl << B.colwise().maxCoeff() << std::endl << std::endl;
  std::cout << "L2-norm of t: " << t.norm() << std::endl << std::endl;
  std::cout << "Number of elements greater than 3 in B: " << (B.array() > 3.0).count() << std::endl << std::endl;
}
