/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MOOSEMESH_H
#define MOOSEMESH_H

#include "InputParameters.h"
#include "MooseObject.h"
#include "BndNode.h"
#include "Moose.h"

// libMesh
#include "mesh.h"
#include "boundary_info.h"
#include "elem_range.h"
#include "node_range.h"
#include "periodic_boundaries.h"

#include <map>

//forward declaration
class MeshModifier;

typedef StoredRange<std::set<Node *>::iterator, Node*> SemiLocalNodeRange;

class MooseMesh;

template<>
InputParameters validParams<MooseMesh>();

// NOTE: maybe inheritance would be better here
//
class MooseMesh : public MooseObject
{
public:
  MooseMesh(const std::string & name, InputParameters parameters);
  MooseMesh(const MooseMesh & other_mesh);
  virtual ~MooseMesh();

  virtual unsigned int dimension() { return _mesh.mesh_dimension(); }

  std::vector<BoundaryID> boundary_ids (const Elem *const elem, const unsigned short int side) const { return _mesh.boundary_info->boundary_ids(elem, side); }
  const std::set<BoundaryID> & get_boundary_ids () const { return _mesh.boundary_info->get_boundary_ids(); }

  void buildNodeList ();

  virtual bnd_node_iterator bnd_nodes_begin ();
  virtual bnd_node_iterator bnd_nodes_end ();

  void build_node_list_from_side_list() { _mesh.boundary_info->build_node_list_from_side_list(); }
  void build_side_list(std::vector<unsigned int> & el, std::vector<unsigned short int> & sl, std::vector<short int> & il) { _mesh.boundary_info->build_side_list(el, sl, il); }
  unsigned int side_with_boundary_id(const Elem * const elem, const BoundaryID boundary_id) const { return _mesh.boundary_info->side_with_boundary_id(elem, boundary_id); }

  MeshBase::const_node_iterator local_nodes_begin() { return _mesh.local_nodes_begin(); }
  MeshBase::const_node_iterator local_nodes_end() { return _mesh.local_nodes_end(); }

  MeshBase::const_element_iterator active_local_elements_begin() { return _mesh.active_local_elements_begin(); }
  const MeshBase::const_element_iterator active_local_elements_end() { return _mesh.active_local_elements_end(); }

  virtual unsigned int n_nodes () const { return _mesh.n_nodes(); }
  virtual unsigned int n_elem () const { return _mesh.n_elem(); }

  std::vector<std::vector<unsigned int> > & nodeToElemMap() { return _node_to_elem_map; }

  virtual const Node & node (const unsigned int i) const { return _mesh.node(i); }
  virtual Node & node (const unsigned int i) { return _mesh.node(i); }

  virtual Elem * elem(const unsigned int i) const { return _mesh.elem(i); }

  bool changed() { return _is_changed; }
  void changed(bool state) { _is_changed = state; }

  //bool parallel() { return _is_parallel; }
  //void parallel(bool state) { _is_parallel = state; }

  void meshChanged();

  void updateActiveSemiLocalNodeRange(std::set<unsigned int> & ghosted_elems);

  ConstElemRange * getActiveLocalElementRange();
  NodeRange * getActiveNodeRange();
  SemiLocalNodeRange * getActiveSemiLocalNodeRange();
  ConstNodeRange * getLocalNodeRange();
  ConstBndNodeRange * getBoundaryNodeRange();

  const std::set<SubdomainID> & meshSubdomains() { return _mesh_subdomains; }
  const std::set<BoundaryID> & meshBoundaryIds() { return _mesh_boundary_ids; }

  void read(const std::string file_name);

  void prepare();
  void update();

  /**
   * This will add the boundary ids to be ghosted to this processor
   */
  void addGhostedBoundary(BoundaryID boundary_id) { _ghosted_boundaries.insert(boundary_id); }

  /**
   * This sets the inflation amount for the bounding box for each partition for use in
   * ghosting boundaries
   */
  void setGhostedBoundaryInflation(const std::vector<Real> & inflation) { _ghosted_boundaries_inflation = inflation; }

  std::set<unsigned int> & getGhostedBoundaries() { return _ghosted_boundaries; }

  std::vector<Real> & getGhostedBoundaryInflation() { return _ghosted_boundaries_inflation; }

  void setPatchSize(const unsigned int patch_size) { _patch_size = patch_size; }
  unsigned int getPatchSize() { return _patch_size; }

  operator libMesh::Mesh &(void) { return _mesh; }

  MeshBase & getMesh() { return _mesh; }

  // Mesh Modifiers /////
  void addMeshModifer(const std::string & mod_name, const std::string & name, InputParameters parameters);
  void applyMeshModifications();

  inline void printInfo(std::ostream &os=libMesh::out) { _mesh.print_info(os); }

  std::set<SubdomainID> & getNodeBlockIds(const Node & node);

  std::vector<unsigned int> & getNodeList(short int nodeset_id) { return _node_set_nodes[nodeset_id]; }

  // Get/Set Filename (for meshes read from a file)
  void setFileName(const std::string & file_name) { _file_name = file_name; }
  const std::string & getFileName() const { return _file_name; }

  /**
   * Add a new node to the mesh.  If there is already a node located at the point passed
   * then the node will not be added.  In either case a refernce to the node at that location
   * will be returned
   */
  const Node * addUniqueNode(const Point & p, Real tol=1e-6);

  /**
   * Get the associated BoundaryID for the boundary name.
   *
   * @return param boundary_name The name of the boundary.
   * @return the boundary id from the passed boundary name.
   */
  BoundaryID getBoundaryID(const BoundaryName & boundary_name) const;

  /**
   * Get the associated subdomain ID for the subdomain name.
   *
   * @param subdomain_name The name of the subdomain
   * @return The subdomain id from the passed subdomain name.
   */
  SubdomainID getSubdomainID(const SubdomainName & subdomain_name) const;

  /**
   * Get the associated subdomainIDs for the subdomain names that are passed in.
   *
   * @param subdomain_name The names of the subdomains
   * @return The subdomain ids from the passed subdomain name.
   */
  std::vector<SubdomainID> getSubdomainIDs(const std::vector<SubdomainName> & subdomain_name) const;

  /**
   * This method returns a writable reference to a subdomain name based on the id parameter
   */
  SubdomainName & subdomainName(SubdomainID subdomain_id) { return _mesh.subdomain_name(subdomain_id); }

  /**
   * This method returns a writable reference to a boundary name based on the id parameter
   */
  BoundaryName & boundaryName(BoundaryID boundary_id);

  libMesh::Mesh _mesh;

  /**
   * This routine builds a multip map of boundary ids to matching boundary ids across all periodic boudnaries
   * in the system.  It does this only for active local elements so the list will not be globally complete when
   * run in parallel!
   */
  void buildPeriodicNodeMap(std::multimap<unsigned int, unsigned int> & periodic_node_map, unsigned int var_number, PeriodicBoundaries *pbs) const;

protected:
  /// true if mesh is changed (i.e. after adaptivity step)
  bool _is_changed;

  // bool _is_parallel;           /// True if using a TRUE parallel mesh (ie Nemesis)

  /// Used for generating the semilocal node range
  std::set<Node *> _semilocal_node_list;

  /**
   * A range for use with TBB.  We do this so that it doesn't have
   * to get rebuilt all the time (which takes time).
   */
  ConstElemRange * _active_local_elem_range;
  SemiLocalNodeRange * _active_semilocal_node_range;  ///< active local + active ghosted
  NodeRange * _active_node_range;
  ConstNodeRange * _local_node_range;
  ConstBndNodeRange * _bnd_node_range;

  /// A map of all of the current nodes to the elements that they are connected to.
  std::vector<std::vector<unsigned int> > _node_to_elem_map;

  /**
   * A set of subdomain IDs currently present in the mesh.
   * For parallel meshes, includes subdomains defined on other
   * processors as well.
   */
  std::set<SubdomainID> _mesh_subdomains;

  /**
   * A set of boundary IDs currently present in the mesh.
   * In serial, this is equivalent to the values returned
   * by _mesh.boundary_info->get_boundary_ids().  In parallel,
   * it will contain off-processor boundary IDs as well.
   */
  std::set<BoundaryID> _mesh_boundary_ids;

  std::vector<MeshModifier *> _mesh_modifiers;

  /// array of boundary nodes
  std::vector<BndNode *> _bnd_nodes;
  typedef std::vector<BndNode *>::iterator             bnd_node_iterator_imp;
  typedef std::vector<BndNode *>::const_iterator const_bnd_node_iterator_imp;

  /// list of nodes that belongs to a specified block (domain)
  std::map<unsigned int, std::set<SubdomainID> > _block_node_list;

  /// list of nodes that belongs to a specified nodeset: indexing [nodeset_id] -> <array of node ids>
  std::map<short int, std::vector<unsigned int> > _node_set_nodes;

  std::set<unsigned int> _ghosted_boundaries;
  std::vector<Real> _ghosted_boundaries_inflation;

  /// The number of nodes to consider in the NearestNode neighborhood.
  unsigned int _patch_size;

  /// file_name iff this mesh was read from a file
  std::string _file_name;

  /// Vector of all the Nodes in the mesh for determining when to add a new point
  std::vector<Node *> _node_map;

  void cacheInfo();
  void freeBndNodes();
};

#endif /* MOOSEMESH_H */
