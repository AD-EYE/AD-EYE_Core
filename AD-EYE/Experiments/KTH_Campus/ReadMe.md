# Setting up the KTH Campus Experiment

## Files needed :

* `KTH3d_20191008.dae` : \
The `.dae` file contains the 3D model of KTH. It has to be imported in prescan
as a _"User Library Element"_. (Explained after)

* `map.osm` : \
The `map.osm` files has been extracted from openstreetmap and represents the road network.
It can easily be imported in Prescan (but it has already been done).

* `map2.osm` : \
The second `.osm` file just contains (notably) a part of the DKV street.

## Import the KTH 3D model as a UL Element

When you open the experiment, a error message will say that an element could not be loaded.
In fact, a UL Element is created only locally on the computer, so it needs to be done before opening
the Prescan experiment.

So a User Library Element needs to be added with the name _KTH_3D_ and the model file `KTH3d_20191008.dae`.
Everything else has been let as default. \
If the Element still cannot be loaded by Prescan when opening the experiment, the actor in the Experiment
can be deleted and replaced by the User Library previously created.

The perfect location for the actor is the following :
* Location : __(X, Y, Z) = `(303, -427, 0)`__
* Orientation : __(Bank, Tilt, Heading) = `(0, 0, 2.74)`__

## Import the road network from openstreetmap

The KTH road network is already imported in the `.pex` file. Anyway, here is the method.

Importing `.osm` is possible with Prescan (just with _File -> Import -> OpenStreeMap..._).
However, the roads which are produced will be full of errors. Here, the painfull part begins.

Prescan creates lot of _flex roads_ but uses too much definition points, lots of them can be removed. \
Also, sometimes crosses ends are too short and it produce errors. It can be solved just by increasing it a little bit.

Lots of modifications has to be done patiently, good luck !
