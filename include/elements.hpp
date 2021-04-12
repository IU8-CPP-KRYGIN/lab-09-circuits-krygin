//
// Created by Ivan Krygin on 12.04.2021.
//

#ifndef INCLUDE_ELEMENTS_HPP_
#define INCLUDE_ELEMENTS_HPP_

#include <vector>

struct Power {};

class Element {
 public:
  virtual float CalculateResistance(const Power&) const = 0;
  virtual ~Element() = default;
};

class GroupConnections : public Element {
 protected:
  std::vector<Element*> elements;

 public:
  void addElements(Element* element) { elements.push_back(element); }
};

class SequentialConnections : public GroupConnections {
 public:
  [[nodiscard]] float CalculateResistance(const Power& p) const override {
    float sum = 0.;
    for (Element* element : elements) {
      sum += element->CalculateResistance(p);
    }
    return sum;
  }
};

class ParallelConnections : public GroupConnections {
 public:
  [[nodiscard]] float CalculateResistance(const Power& p) const override {
    float invertedSum = 0.;
    for (Element* element : elements) {
      invertedSum += 1 / element->CalculateResistance(p);
    }
    return 1 / invertedSum;
  }
};

class Resistor : public Element {
 private:
  float resistance;

 public:
  explicit Resistor(float resistance) { this->resistance = resistance; }

  [[nodiscard]] float CalculateResistance(
      [[maybe_unused]] const Power& p) const final {
    return resistance;
  };
};

#endif  // INCLUDE_ELEMENTS_HPP_
