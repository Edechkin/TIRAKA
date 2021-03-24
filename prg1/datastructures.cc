// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <iostream>


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
    // Clear areas also!
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
        //everyPlaceId_.push_back(id);
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
    //std::pair<PlaceID, Name> vittu;
    std::vector<std::pair<PlaceID, Name>> support = {};
    std::vector<PlaceID> alphabetical_order = {};
    if (places_.empty()){
    return {};
    }
    for (auto& id : places_){
        //vittu = std::make_pair(id, id.second.name);
        //std::pair<PlaceID, Name> vittu (id, id.second.name);
        //std::cout << id.first << std::endl;
        //support.push_back(vittu);
    }
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    // Replace this comment with your implementation
    return {};
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
        super_areas_ = {};
        recursive_sub_area_in_areas(id, super_areas_);
        return super_areas_;
    }
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::remove_place(PlaceID id)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    // Replace this comment with your implementation
    return {NO_AREA};
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    // Replace this comment with your implementation
    return NO_AREA;
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
