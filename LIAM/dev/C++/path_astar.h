#ifndef ASTARPATHFINDING_H
#define ASTARPATHFINDING_H

#include <map>
#include <queue>
#include <vector>

class AStarPathfinding
{
  public:
    static std::vector<std::vector<double>> findPathAStar(
        const std::vector<double>& start, const std::vector<double>& goal,
        const std::vector<std::vector<double>>& obstacles);

  private:
    static double calculateHeuristic(const std::vector<double>& current,
                                     const std::vector<double>& goal);
    static bool isPointInObstacle(const std::vector<double>& point,
                                  const std::vector<std::vector<double>>& obstacles, double radius);
};

#endif  // ASTARPATHFINDING_H