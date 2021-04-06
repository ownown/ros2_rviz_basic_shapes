# ROS2 RViz test

Partial conversion of the ROS RViz [Basic Shapes](https://wiki.ros.org/rviz/Tutorials/Markers%3A%20Basic%20Shapes) tutorial into ROS2.

I've not bothered doing the shape changing element, and I've moved it into a class instead of just being in a loop.

In RViz, you need to set Fixed Frame to `my_frame` and add a Marker with topic `/my_marker`.
