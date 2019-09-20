C++ Node Architecture
=================

This file describe the architecture that C++ ROS Node should to follow in the AD-EYE platform.
These rules attend to help producing a readable code.

## Overall Notes
The main idea is to have a clean and readable code in order to be easy to maintain.
Then every common sense rule of having a clean and organized code is welcome in addition to the following guidelines.

## Class
We usually use classes to implement a C++ Node.
They should follow the following architecture:

#### Attributes
Just after the class declaration we define all the attributes (organized as possible).
They come first so we can easily know what we are working with.

_Note: the `private` word is recommended (for readability) but not necessary as `class` keyword sets `private` by default._

#### Constructor
Then the first method that should appear is the constructor.
It initialize the member `ros::NodeHandle` reference and all other attributes.
Then we initialize the publishers and the subscribers.

_Note: Here the `public` keyword is necessary._

Even if variables are not initialized in the right order, we should clearly distinguish categories at the first look.

#### Callbacks
Then, we can define every callbacks that will be called by topic subscriptions.

#### Run method
After callbacks, a _running_ method needs to be implemented. The name of the method should follow the logic of the Node. This method contains main instructions of the Node. It is where the `ros::spin()` call should be.

_Note: Another possible way is to call `ros::spin()` at the end of the `main` function and to call this_ running _method inside a callback._

#### Other methods
Any other function that the Node use, for any purpose will be implemented after.

## main function
Last but not least, the main function is implemented. If every previous rules has been respected, it should looks like the following, just creating the Node and eventually calling the _run_ method (If it hasn't been done inside the constructor).

```cpp
int main(int argc, char **argv)
{
	ros::init(argc, argv, "<NodeName>");
	ros::NodeHandle nh;

	StraightControler <NodeName>(nh);
	<NodeName>.run();
}
```

_Note: Using a reference attribute to the `ros::NodeHandle` in the Node is recommended as it avoid having multiple useless copies of the `ros::NodeHandle`:_

```cpp
class <NodeName>
{
private:
  [...]
	ros::NodeHandle& _nh;

public:
	<NodeName>(ros::NodeHandle& nh) : _nh(nh) {
    [...]
    }
  [...]
};
```
