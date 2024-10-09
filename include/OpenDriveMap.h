#pragma once
#include "Junction.h"
#include "Road.h"
#include "Lane.h"
#include "LaneSection.h"
#include "RoadNetworkMesh.h"
#include "RoutingGraph.h"

#include <pugixml/pugixml.hpp>

#include <map>
#include <string>
#include <vector>
#include <optional>

namespace odr
{

class OpenDriveMap
{
public:
    OpenDriveMap(const std::string& xodr_file,
                 const bool         center_map = false,
                 const bool         with_road_objects = false,
                 const bool         with_lateral_profile = true,
                 const bool         with_lane_height = false,
                 const bool         abs_z_for_for_local_road_obj_outline = false,
                 const bool         fix_spiral_edge_cases = true,
                 const bool         with_road_signals = true,
                 const bool         exclude_non_driving_lanes = false);

    std::vector<Road>     get_roads() const;
    std::vector<Junction> get_junctions() const;

    RoadNetworkMesh get_road_network_mesh(const double eps) const;
    RoutingGraph    get_routing_graph() const;
    road_st         get_curr_topo_pos(const double x, const double y) const;

    std::optional<Lane>        get_connecting_lane(const Lane& lane, bool predecessors, std::optional<LaneSection> target_lanesection) const;
    std::optional<LaneSection> adjacent_lanesection(const Road& current_road, const LaneSection& current_lanesection, bool predecessors) const;

    std::string            proj4 = "";
    double                 x_offs = 0;
    double                 y_offs = 0;
    const std::string      xodr_file = "";
    pugi::xml_document     xml_doc;
    pugi::xml_parse_result xml_parse_result;

    std::map<std::string, Road>     id_to_road;
    std::map<std::string, Junction> id_to_junction;
};

} // namespace odr