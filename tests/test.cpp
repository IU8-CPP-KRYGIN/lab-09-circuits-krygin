//
// Created by Ivan Krygin on 12.04.2021.
//

#include <gtest/gtest.h>

#include <elements.hpp>

TEST(Resistor, CalculatesResistance) {
  float resistance = 27.;

  Resistor r(resistance);
  Power p;

  float actualResistance = r.CalculateResistance(p);

  EXPECT_EQ(resistance, actualResistance);
}

TEST(Resistor, SenqualConnection) {
  float resistance1 = 27.;
  float resistance2 = 33.;

  auto* r1 = new Resistor(resistance1);
  auto* r2 = new Resistor(resistance2);
  Power p;

  SequentialConnections c;
  c.addElements(r1);
  c.addElements(r2);

  float actualResistance = c.CalculateResistance(p);

  EXPECT_FLOAT_EQ(60., actualResistance);
}

TEST(Resistor, ParallelConnection) {
  float resistance1 = 27.;
  float resistance2 = 33.;

  auto* r1 = new Resistor(resistance1);
  auto* r2 = new Resistor(resistance2);
  Power p;

  ParallelConnections c;
  c.addElements(r1);
  c.addElements(r2);

  float actualResistance = c.CalculateResistance(p);

  EXPECT_FLOAT_EQ(14.85, actualResistance);
}