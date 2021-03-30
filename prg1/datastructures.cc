// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <iostream>

#include <cmath>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{
   return places_.size();
}

void Datastructures::clear_all()
{
    places_.clear();
    areas_.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> places = {};
    for (const auto& id : places_){
        places.push_back(id.first);
    }
    return places;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    place newPlace = {name, type, xy};
    if (places_.find(id) == places_.end()) {
        places_.insert({id, newPlace});
        return true;
    }
    return false;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    if (places_.find(id) == places_.end()) {
        return {NO_NAME, PlaceType::NO_TYPE};
    }
    else {
        return {places_.at(id).name, places_.at(id).type };
    }
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    if (places_.find(id) == places_.end()) {
        return { NO_COORD};
    }
    else {
        return {places_.at(id).xy };
    }
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{

    if (areas_.find(id) == areas_.end()) {
        area new_area = {name, coords, {}, NO_AREA};
        areas_.insert({id, new_area});
        return true;
    }
    return false;
}

Name Datastructures::get_area_name(AreaID id)
{
    if (areas_.find(id) == areas_.end()) {
        return {NO_NAME};
    }
    else {
        return {areas_.at(id).name};
    }
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    if (areas_.find(id) == areas_.end()) {
        return {NO_COORD};
    }
    else {
        return {areas_.at(id).coords};
    }
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    if (places_.empty()){
        return {};
    }

    std::vector<std::pair<Name, PlaceID>> tmp = {};
    std::vector<PlaceID> alphabetical = {};
    for (auto pair : places_) {
        tmp.push_back(std::make_pair( pair.second.name, pair.first));
    }
    sort(tmp.begin(), tmp.end());
    for (auto i : tmp) {
        alphabetical.push_back(i.second);
    }
    return alphabetical;

}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    if (places_.empty())
        return {};
    else {
        std::vector<std::pair<Coord, PlaceID>> tmp = {};
        std::vector<PlaceID> coord_order = {};
        for (auto pair : places_) {
            tmp.push_back(std::make_pair( pair.second.xy, pair.first));
        }

        sort(tmp.begin(), tmp.end(),
             [](std::pair<Coord, PlaceID> a, std::pair<Coord, PlaceID> b)->bool
        {int da = sqrt(pow(a.first.x,2)+pow(a.first.y,2));
         int db = sqrt(pow(b.first.x,2)+pow(b.first.y,2));
         if ( da == db) {
             return a.first.y < b.first.y;
         }
         else{
             return da < db;}
        });
        for (auto i : tmp) {
            coord_order.push_back(i.second);
        }
        return coord_order;

    }

}


std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> places_with_names = {};
    for (auto& id : places_){
        if (id.second.name == name){
            places_with_names.push_back(id.first);
        }
    }
    return places_with_names;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> places_with_types = {};
    for (auto& id : places_){
        if (id.second.type == type){
            places_with_types.push_back(id.first);
        }
    }
    return places_with_types;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if (places_.find(id) == places_.end()) {
        return false;
    }
    else {
        Name name = places_.at(id).name;
        Name tmp = newname;
        places_.at(id).name = newname;
        return true;
    }
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if (places_.find(id) == places_.end()) {
        return false;
    }
    else {
        places_.at(id).xy = newcoord;
        return true;
    }
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<AreaID> areas = {};
    for (const auto& id : areas_){
        areas.push_back(id.first);
    }
    return areas;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if (areas_.find(id) == areas_.end() || areas_.find(parentid) == areas_.end()) {
        return false;
    }
    else if (areas_.at(id).super_area != NO_AREA) {
        return false;
    }
    else {
        AreaID superareaID = parentid;
        areas_.at(id).super_area = superareaID;
        AreaID subareaID = id;
        areas_.at(parentid).sub_areas.push_back(subareaID);
        return true;
    }
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    if (areas_.at(id).super_area == NO_AREA) {
        return {NO_AREA};
    }
    else {
        std::vector<PlaceID> super_areas = {};
        recursive_sub_area_in_areas(id, super_areas);
        return super_areas;
    }
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    if (places_.empty()){
        return {NO_PLACE};
    }


        struct p{
            int dist;
            PlaceID id;
            int c;

        };
        std::vector<struct p> tmp = {};
        std::vector<PlaceID> closest = {};
        if ( type == PlaceType::NO_TYPE){
            for (auto pair : places_){
                int dist = sqrt(pow((pair.second.xy.x-xy.x),2)+pow((pair.second.xy.y-xy.y),2));
                p help = {dist, pair.first, pair.second.xy.y};
                tmp.push_back(help);
            }
        }
        else {
            for (auto pair : places_){
                if(type == pair.second.type){
                    int dist = sqrt(pow((pair.second.xy.x-xy.x),2)+pow((pair.second.xy.y-xy.y),2));
                    p help = {dist, pair.first, pair.second.xy.y};
                    tmp.push_back(help);
                }
            }
        }
        sort(tmp.begin(), tmp.end(),
             [](p a, p b){
            if (a.dist == b.dist) {
                return a.c < b.c;
            }
            return a.dist < b.dist;
            });
    if (tmp.size() == 1){
        closest.push_back(tmp.at(0).id);
    }
    else if (tmp.size() == 2){
        closest.push_back(tmp.at(0).id);
        closest.push_back(tmp.at(1).id);
    }
    else {
        closest.push_back(tmp.at(0).id);
        closest.push_back(tmp.at(1).id);
        closest.push_back(tmp.at(2).id);
    }
    return closest;

}


bool Datastructures::remove_place(PlaceID id)
{
    if (places_.find(id) == places_.end()) {
        return false;
    }
    else {
        Name name = places_.at(id).name;
        places_.erase(id);
        return true;
    }
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    if (areas_.find(id) == areas_.end()){
        return {NO_AREA};
    }
    else if (areas_.at(id).sub_areas.empty()) {
        return {NO_AREA};
    }

    else {
        std::vector<PlaceID> sub_areas = {};
        recursive_all_sub_areas_in_area(id, sub_areas);
        return sub_areas;
    }
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
   //int SUP = -1;
   if (areas_.find(id1) == areas_.end() || areas_.find(id2) == areas_.end()){
       return NO_AREA;
   }
   std::vector<AreaID> v1 = subarea_in_areas(id1);
   std::vector<AreaID> v2 = subarea_in_areas(id2);
   if (v1.empty() || v2.empty()){
       return NO_AREA;

   }
   if (v1.size() < v2.size()) {
        int iter1 = 0;
        int iter2 = v2.size() - v1.size();
        while (iter1 < (v1.size())) {
            if (v1.at(iter1) == v2.at(iter2)){
                return v1.at(iter1);
            }
            iter1 += 1;
            iter2 += 1;

        }
        return NO_AREA;
   }
   else if (v1.size() > v2.size()) {
       int iter2 = 0;
       int iter1 = v1.size() - v2.size();
       while (iter2 < (v2.size())) {
           if (v1.at(iter1) == v2.at(iter2)){
               return v1.at(iter1);
           }
           iter1 += 1;
           iter2 += 1;

       }
       return NO_AREA;
   }
   else {
       int iter = 0;
       int test = v2.size();
       while (iter < (v2.size())) {
           if (v1.at(iter) == v2.at(iter)){
               /*if (iter == 1){
                   return NO_AREA;
               }*/
               return v1.at(iter);
           }
           iter += 1;

       }
       return NO_AREA;
   }

}

std::vector<AreaID> Datastructures::recursive_sub_area_in_areas(AreaID id, std::vector<AreaID> &superareas)
{


    if (areas_.at(id).super_area == NO_AREA) {
        return superareas;
    }
    else {
        AreaID ptr = areas_.at(id).super_area;
        superareas.push_back(ptr);
        return recursive_sub_area_in_areas(ptr, superareas);
    }
}

std::vector<AreaID> Datastructures::recursive_all_sub_areas_in_area(AreaID id, std::vector<AreaID> &subareas)
{
    if (areas_.at(id).sub_areas.empty()) {
        return subareas;
    }

    for (AreaID sub : areas_.at(id).sub_areas){
        subareas.push_back(sub);
        recursive_all_sub_areas_in_area(sub, subareas);

    }
    return subareas;

}


