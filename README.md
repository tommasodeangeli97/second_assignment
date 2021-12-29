Second assignment
================================

this assignment consist in control a robot in a circuit and create a service for the speed regulation and for reset the position.

Installing and running
----------------------

to run the assignment it's needed to have installed ros on your pc.

download the package.

to run the nodes:

go to "world" folder in the "second_assignment" package and to run the simulation write the command $rosrun stage_ros stageros my_world.world 

now you can run the "controllo" node with $rosrun second_assignment controllo   //the controllo node waits

to make the robot move you have to run $rosrun second_assignment plus   // is the node that gives the velocity to "controllo" and gives also the instructions to use the service 

to make the service start $rosservice call manualplus -stab-   //there you can encrease, decrease the velocity of the robot and you can reset the position

## explanation for the code
----------------------

Controllo
---------

I create a publisher and subscriber node to control the position of the robot and to make him turn.
In the main I only create the NodeHandle to make the node communicate with the ros sistem and i call the Callback.
In the Callback i watch the distance between the robot and the guide lines and i decide in which direction the robot had to turn picking the maximum distance for the right part, the maximum distance for the straith part and the maximum distance for the left part and confronting the results.
The linear velocity of the robot is given by the service node.

Plus
---------

this is the service node where i give the velocity seeing what the user instructions are.
In the main i call the function "add" where I confront the inputs given by the user and I execute the request, the results are given to "controllo" for making the robot move

Manualplus
---------

this is the service where I define the request and the answer, in this case the request is a string and the answer is a float32.

## topic used
-----------------------

to see the distance between the robot and the circuit I subscribe the information given by the /base_scan topic 
to modify the velocity and the angulation of the robot I publish on the /cmd_vel topic 

(those topic were already created)
