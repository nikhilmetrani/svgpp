#include <svgpp/unitless_length_factory.hpp>

#include <gtest/gtest.h>

TEST(LengthFactory, base)
{
  svgpp::unitless_length_factory_absolute<double, double, svgpp::tag::length_units::in> factory;
  factory.set_absolute_units_coefficient(90, svgpp::tag::length_units::in()); // 90 dpi
  EXPECT_NEAR(1.25, factory.create_length(1, svgpp::tag::length_units::pt()), 1e-8);
  EXPECT_NEAR(3.75, factory.create_length(3, svgpp::tag::length_units::pt()), 1e-8);
  EXPECT_NEAR(15, factory.create_length(1, svgpp::tag::length_units::pc()), 1e-8);
  EXPECT_NEAR(3.543307, factory.create_length(1, svgpp::tag::length_units::mm()), 1e-5);
  EXPECT_NEAR(35.43307, factory.create_length(1, svgpp::tag::length_units::cm()), 1e-5);
  EXPECT_NEAR(90, factory.create_length(1, svgpp::tag::length_units::in()), 1e-8);
}

TEST(LengthFactory, full)
{
  svgpp::unitless_length_factory<> factory;
  factory.set_absolute_units_coefficient(90, svgpp::tag::length_units::in()); // 90 dpi
  factory.set_viewport_size(250, 120);
  EXPECT_NEAR(1.25, factory.create_length(1, svgpp::tag::length_units::pt()), 1e-8);
  EXPECT_NEAR(3.75, factory.create_length(3, svgpp::tag::length_units::pt()), 1e-8);
  EXPECT_NEAR(15, factory.create_length(1, svgpp::tag::length_units::pc()), 1e-8);
  EXPECT_NEAR(3.543307, factory.create_length(1, svgpp::tag::length_units::mm()), 1e-5);
  EXPECT_NEAR(35.43307, factory.create_length(1, svgpp::tag::length_units::cm()), 1e-5);
  EXPECT_NEAR(90, factory.create_length(1, svgpp::tag::length_units::in()), 1e-8);

  EXPECT_NEAR(125, factory.create_length(50, svgpp::tag::length_units::percent(), svgpp::tag::width_length()), 1e-8);
  EXPECT_NEAR(60, factory.create_length(50, svgpp::tag::length_units::percent(), svgpp::tag::height_length()), 1e-8);
  EXPECT_NEAR(std::sqrt(250 * 250 + 120 * 120)/std::sqrt(2)/2, 
    factory.create_length(50, svgpp::tag::length_units::percent(), svgpp::tag::not_width_nor_height_length()), 1e-8);

  factory.set_viewport_size(300, 300);
  EXPECT_NEAR(270, factory.create_length(90, svgpp::tag::length_units::percent(), svgpp::tag::not_width_nor_height_length()), 1e-8);

  factory.set_user_units_coefficient(777);
  EXPECT_NEAR(77.7, factory.create_length(0.1, svgpp::tag::length_units::px()), 1e-8);
  EXPECT_NEAR(77.7, factory.create_length(0.1, svgpp::tag::length_units::none()), 1e-8);

  factory.set_absolute_units_coefficient(333, svgpp::tag::length_units::pc());
  factory.set_ex_coefficient(22, svgpp::tag::length_units::pc());
  factory.set_em_coefficient(77, svgpp::tag::length_units::pc());
  EXPECT_NEAR(22*333*2, factory.create_length(2, svgpp::tag::length_units::ex()), 1e-8);
  EXPECT_NEAR(77*333*3, factory.create_length(3, svgpp::tag::length_units::em()), 1e-8);
}