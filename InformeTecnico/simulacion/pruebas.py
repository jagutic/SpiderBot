import pybullet as p
import pybullet_data
import numpy as np
import time


def constrain_links(robot_id, l1, l2, world_point):
    parent_state = p.getLinkState(robot_id, l1)
    child_state  = p.getLinkState(robot_id, l2)

    parent_pos, parent_orn = parent_state[0], parent_state[1]
    child_pos, child_orn   = child_state[0], child_state[1]

    parent_rot = np.array(p.getMatrixFromQuaternion(parent_orn)).reshape(3,3)
    child_rot  = np.array(p.getMatrixFromQuaternion(child_orn)).reshape(3,3)

    # Convertir el punto global a local en cada link
    parent_local = parent_rot.T.dot(world_point - np.array(parent_pos))
    child_local  = child_rot.T.dot(world_point - np.array(child_pos))

    cid = p.createConstraint(
        parentBodyUniqueId=robot_id,
        parentLinkIndex=l1,
        childBodyUniqueId=robot_id,
        childLinkIndex=l2,
        jointType=p.JOINT_POINT2POINT,
        jointAxis=[0,0,0],
        parentFramePosition=parent_local,
        childFramePosition=child_local
    )

    #p.changeConstraint(cid, maxForce=5000, erp=0.NUM)


# Conectarse a PyBullet en modo GUI
p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0,0,-9.8)
p.setRealTimeSimulation(0)

p.resetDebugVisualizerCamera(
    cameraDistance=0.5,
    cameraYaw=90+90,
    cameraPitch=-15,
    cameraTargetPosition=[0,0,0]
)

p.setPhysicsEngineParameter(
    fixedTimeStep=1/240,
    numSolverIterations=200,
    numSubSteps=10,
    erp=0.001,
    contactERP=0.01,
    frictionERP=0.01,

)
NUM = 2

plane_id = p.loadURDF("plane.urdf")
robot_id = p.loadURDF("unnamed/urdf/unnamed.urdf", basePosition=[0, 0, 0.1])
# #box_id = p.loadURDF("box.urdf", basePosition=[0, 0, 0.NUM])
caja =True
if not caja:
    # NUM leg izq
    world_point = np.array([0.043044, 0.066277, 0.07186 + 0.1])
    constrain_links(robot_id, 9, 24, world_point)

    world_point = np.array([0.038881, 0.062534, 0.028655 + 0.1])
    constrain_links(robot_id, 6, 21, world_point)
    # NUM leg der
    world_point = np.array([-0.043044, 0.066277, 0.07186 + 0.1])
    constrain_links(robot_id, 12, 23, world_point)

    world_point = np.array([-0.038881, 0.062534, 0.028655 + 0.1])
    constrain_links(robot_id, 3, 22, world_point)

    # 2 leg der
    world_point = np.array([-0.053201, 0.081, 0.060165 + 0.1])
    constrain_links(robot_id, 13, 18, world_point)

    world_point = np.array([-0.043141, 0.084313, 0.029006 + 0.1])
    constrain_links(robot_id, 4, 17, world_point)

    # # 2 leg izq
    world_point = np.array([0.053202, 0.08775, 0.060164 + 0.1])

    constrain_links(robot_id, 10, 20, world_point)

    world_point = np.array([0.043, 0.08675, 0.029009 + 0.1])
    constrain_links(robot_id, 7, 19, world_point)




    # 3 leg izq
    world_point = np.array([0.043488, -0.067507, 0.071347 + 0.1])
    constrain_links(robot_id, 30, 46, world_point)

    world_point = np.array([0.038548, -0.06375, 0.028603 + 0.1])
    constrain_links(robot_id, 33, 45, world_point)
    # 3 leg der
    world_point = np.array([-0.043909, -0.067507, 0.071817 + 0.1])
    constrain_links(robot_id, 27, 48, world_point)

    world_point = np.array([-0.038876, -0.062507, 0.02859 + 0.1])
    constrain_links(robot_id, 37, 47, world_point)

    # 4 leg der
    world_point = np.array([-0.043, -0.08275, 0.029009 + 0.1])
    constrain_links(robot_id, 41, 36, world_point)

    world_point = np.array([-0.053202, -0.08775, 0.060164 + 0.1])
    constrain_links(robot_id, 28, 42, world_point)

    # 4 leg izq
    world_point = np.array([0.053202, -0.08775, 0.060164 + 0.1])
    constrain_links(robot_id, 31, 44, world_point)

    world_point = np.array([0.042673, -0.084445, 0.029094 + 0.1])
    constrain_links(robot_id, 34, 43, world_point)

    mtr = 14
    mtr_2 = 38


if (caja):
    # NUM leg izq
    world_point = np.array([0.043044, 0.066277, 0.07186 + 0.1])
    constrain_links(robot_id, 9 + NUM, 24 + NUM, world_point)

    world_point = np.array([0.038881, 0.062534, 0.028655 + 0.1])
    constrain_links(robot_id, 6 + NUM, 21 + NUM, world_point)
    # NUM leg der
    world_point = np.array([-0.043044, 0.066277, 0.07186 + 0.1])
    constrain_links(robot_id, 12 + NUM, 23 + NUM, world_point)

    world_point = np.array([-0.038881, 0.062534, 0.028655 + 0.1])
    constrain_links(robot_id, 3 + NUM, 22 + NUM, world_point)

    # 2 leg der
    world_point = np.array([-0.053201, 0.081, 0.060165 + 0.1])
    constrain_links(robot_id, 13 + NUM, 18 + NUM, world_point)

    world_point = np.array([-0.043141, 0.084313, 0.029006 + 0.1])
    constrain_links(robot_id, 4 + NUM, 17 + NUM, world_point)

    # # 2 leg izq
    world_point = np.array([0.053202, 0.08775, 0.060164 + 0.1])

    constrain_links(robot_id, 10 + NUM, 20 + NUM, world_point)

    world_point = np.array([0.043, 0.08675, 0.029009 + 0.1])
    constrain_links(robot_id, 7 + NUM, 19 + NUM, world_point)



    # 3 leg izq
    world_point = np.array([0.043488, -0.067507, 0.071347 + 0.1])
    constrain_links(robot_id, 30 + NUM, 46 + NUM, world_point)

    world_point = np.array([0.038548, -0.06375, 0.028603 + 0.1])
    constrain_links(robot_id, 33 + NUM, 45 + NUM, world_point)
    # 3 leg der
    world_point = np.array([-0.043909, -0.067507, 0.071817 + 0.1])
    constrain_links(robot_id, 27 + NUM, 48 + NUM, world_point)

    world_point = np.array([-0.038876, -0.062507, 0.02859 + 0.1])
    constrain_links(robot_id, 37 + NUM, 47 + NUM, world_point)

    # 4 leg der
    world_point = np.array([-0.043, -0.08275, 0.029009 + 0.1])
    constrain_links(robot_id, 41 + NUM, 36 + NUM, world_point)

    world_point = np.array([-0.053202, -0.08775, 0.060164 + 0.1])
    constrain_links(robot_id, 28 + NUM, 42 + NUM, world_point)

    # 4 leg izq
    world_point = np.array([0.053202, -0.08775, 0.060164 + 0.1])
    constrain_links(robot_id, 31 + NUM, 44 + NUM, world_point)

    world_point = np.array([0.042673, -0.084445, 0.029094 + 0.1])
    constrain_links(robot_id, 34 + NUM, 43 + NUM, world_point)
    mtr = 14 + NUM
    mtr_2 = 38 + NUM




# Obtener número de articulaciones
num_joints = p.getNumJoints(robot_id)
print(f"Número de articulaciones: {num_joints}")
num_joints = p.getNumJoints(robot_id)

print("Índice | Joint Name | Link Name")
print("------------------------------------")

for i in range(num_joints):
    info = p.getJointInfo(robot_id, i)
    joint_name = info[1].decode('utf-8')
    link_name = info[12].decode('utf-8')
    print(f"{i:>6} | {joint_name:<20} | {link_name}")


slider = p.addUserDebugParameter(joint_name + "_vel", -100, 100, 0)


slider_2 = p.addUserDebugParameter(joint_name + "_vel", -100, 100, 0)


for j in range(num_joints):
    p.setJointMotorControl2(robot_id, j, p.VELOCITY_CONTROL, force=0)
# Bucle principal
while True:
    
    val = p.readUserDebugParameter(slider)
    p.setJointMotorControl2(
        bodyUniqueId=robot_id,
        jointIndex=mtr,
        controlMode=p.VELOCITY_CONTROL,
        targetVelocity=val,  # multiplica para ajustar velocidad
        force=25
    )
    val = p.readUserDebugParameter(slider_2)
    p.setJointMotorControl2(
        bodyUniqueId=robot_id,
        jointIndex=mtr_2,
        controlMode=p.VELOCITY_CONTROL,
        targetVelocity=val,  # multiplica para ajustar velocidad
        force=25
    )

    p.stepSimulation()
    time.sleep(1. / 240.)
