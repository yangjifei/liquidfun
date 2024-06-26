set(BOX2D_Api_SRCS
	API/api.cpp
)
set(BOX2D_Api_HDRS
	Api/api_body.h
	Api/api_contacts.h
	Api/api_fixture.h
	Api/api_joint.h
	Api/api_particlegroups.h
	Api/api_particles.h
	Api/api_particlesystem.h
	Api/api_raycast.h
	Api/api_shape.h
	Api/api_utility.h
	Api/api_world.h
	Api/api.h
)
set(BOX2D_Unity_HDRS
	Unity/IUnityEventQueue.h
	Unity/IUnityGraphics.h
	Unity/IUnityGraphicsD3D11.h
	Unity/IUnityGraphicsD3D12.h
	Unity/IUnityGraphicsMetal.h
	Unity/IUnityGraphicsVulkan.h
	Unity/IUnityInterface.h
	Unity/IUnityProfiler.h
	Unity/IUnityProfilerCallbacks.h
	Unity/IUnityRenderingExtensions.h
	Unity/IUnityShaderCompilerAccess.h
	Unity/UnityAndroidAsset.h
)
set(BOX2D_Collision_SRCS
	Collision/b2BroadPhase.cpp
	Collision/b2CollideCircle.cpp
	Collision/b2CollideEdge.cpp
	Collision/b2CollidePolygon.cpp
	Collision/b2Collision.cpp
	Collision/b2Distance.cpp
	Collision/b2DynamicTree.cpp
	Collision/b2TimeOfImpact.cpp
)
set(BOX2D_Collision_HDRS
	Collision/b2BroadPhase.h
	Collision/b2Collision.h
	Collision/b2Distance.h
	Collision/b2DynamicTree.h
	Collision/b2TimeOfImpact.h
)
set(BOX2D_Shapes_SRCS
	Collision/Shapes/b2CircleShape.cpp
	Collision/Shapes/b2EdgeShape.cpp
	Collision/Shapes/b2ChainShape.cpp
	Collision/Shapes/b2PolygonShape.cpp
)
set(BOX2D_Shapes_HDRS
	Collision/Shapes/b2CircleShape.h
	Collision/Shapes/b2EdgeShape.h
	Collision/Shapes/b2ChainShape.h
	Collision/Shapes/b2PolygonShape.h
	Collision/Shapes/b2Shape.h
)
set(BOX2D_Common_SRCS
	Common/b2BlockAllocator.cpp
	Common/b2Draw.cpp
	Common/b2FreeList.cpp
	Common/b2Math.cpp
	Common/b2Settings.cpp
	Common/b2StackAllocator.cpp
	Common/b2Stat.cpp
	Common/b2Timer.cpp
	Common/b2TrackedBlock.cpp
)
set(BOX2D_Common_HDRS
	Common/b2BlockAllocator.h
	Common/b2Draw.h
	Common/b2FreeList.h
	Common/b2GrowableStack.h
	Common/b2GrowableBuffer.h
	Common/b2IntrusiveList.h
	Common/b2Math.h
	Common/b2Settings.h
	Common/b2SlabAllocator.h
	Common/b2StackAllocator.h
	Common/b2Stat.h
	Common/b2Timer.h
	Common/b2TrackedBlock.h
)
set(BOX2D_Dynamics_SRCS
	Dynamics/b2Body.cpp
	Dynamics/b2ContactManager.cpp
	Dynamics/b2Fixture.cpp
	Dynamics/b2Island.cpp
	Dynamics/b2World.cpp
	Dynamics/b2WorldCallbacks.cpp
)
set(BOX2D_Dynamics_HDRS
	Dynamics/b2Body.h
	Dynamics/b2ContactManager.h
	Dynamics/b2Fixture.h
	Dynamics/b2Island.h
	Dynamics/b2TimeStep.h
	Dynamics/b2World.h
	Dynamics/b2WorldCallbacks.h
)
set(BOX2D_Contacts_SRCS
	Dynamics/Contacts/b2CircleContact.cpp
	Dynamics/Contacts/b2Contact.cpp
	Dynamics/Contacts/b2ContactSolver.cpp
	Dynamics/Contacts/b2PolygonAndCircleContact.cpp
	Dynamics/Contacts/b2EdgeAndCircleContact.cpp
	Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
	Dynamics/Contacts/b2ChainAndCircleContact.cpp
	Dynamics/Contacts/b2ChainAndPolygonContact.cpp
	Dynamics/Contacts/b2PolygonContact.cpp
)
set(BOX2D_Contacts_HDRS
	Dynamics/Contacts/b2CircleContact.h
	Dynamics/Contacts/b2Contact.h
	Dynamics/Contacts/b2ContactSolver.h
	Dynamics/Contacts/b2PolygonAndCircleContact.h
	Dynamics/Contacts/b2EdgeAndCircleContact.h
	Dynamics/Contacts/b2EdgeAndPolygonContact.h
	Dynamics/Contacts/b2ChainAndCircleContact.h
	Dynamics/Contacts/b2ChainAndPolygonContact.h
	Dynamics/Contacts/b2PolygonContact.h
)
set(BOX2D_Joints_SRCS
	Dynamics/Joints/b2DistanceJoint.cpp
	Dynamics/Joints/b2FrictionJoint.cpp
	Dynamics/Joints/b2GearJoint.cpp
	Dynamics/Joints/b2Joint.cpp
	Dynamics/Joints/b2MotorJoint.cpp
	Dynamics/Joints/b2MouseJoint.cpp
	Dynamics/Joints/b2MotorJoint.cpp
	Dynamics/Joints/b2PrismaticJoint.cpp
	Dynamics/Joints/b2PulleyJoint.cpp
	Dynamics/Joints/b2RevoluteJoint.cpp
	Dynamics/Joints/b2RopeJoint.cpp
	Dynamics/Joints/b2WeldJoint.cpp
	Dynamics/Joints/b2WheelJoint.cpp
)
set(BOX2D_Joints_HDRS
	Dynamics/Joints/b2DistanceJoint.h
	Dynamics/Joints/b2FrictionJoint.h
	Dynamics/Joints/b2GearJoint.h
	Dynamics/Joints/b2Joint.h
	Dynamics/Joints/b2MotorJoint.h
	Dynamics/Joints/b2MouseJoint.h
	Dynamics/Joints/b2PrismaticJoint.h
	Dynamics/Joints/b2PulleyJoint.h
	Dynamics/Joints/b2RevoluteJoint.h
	Dynamics/Joints/b2RopeJoint.h
	Dynamics/Joints/b2WeldJoint.h
	Dynamics/Joints/b2WheelJoint.h
)
set(BOX2D_Particle_SRCS
	Particle/b2Particle.cpp
	Particle/b2ParticleGroup.cpp
	Particle/b2ParticleSystem.cpp
	Particle/b2VoronoiDiagram.cpp
)
set(BOX2D_Particle_HDRS
	Particle/b2Particle.h
	Particle/b2ParticleGroup.h
	Particle/b2ParticleSystem.h
	Particle/b2StackQueue.h
	Particle/b2VoronoiDiagram.h
)
set(BOX2D_Rope_SRCS
	Rope/b2Rope.cpp
)
set(BOX2D_Rope_HDRS
	Rope/b2Rope.h
)
set(BOX2D_General_HDRS
	Box2D.h
)
include_directories( ../ )

if(BOX2D_BUILD_SHARED)
	add_library(Box2D_shared SHARED
		${BOX2D_Unity_HDRS}
		${BOX2D_General_HDRS}
		${BOX2D_Joints_SRCS}
		${BOX2D_Joints_HDRS}
		${BOX2D_Contacts_SRCS}
		${BOX2D_Contacts_HDRS}
		${BOX2D_Dynamics_SRCS}
		${BOX2D_Dynamics_HDRS}
		${BOX2D_Common_SRCS}
		${BOX2D_Common_HDRS}
		${BOX2D_Shapes_SRCS}
		${BOX2D_Shapes_HDRS}
		${BOX2D_Collision_SRCS}
		${BOX2D_Collision_HDRS}
		${BOX2D_Particle_SRCS}
		${BOX2D_Particle_HDRS}
		${BOX2D_Rope_SRCS}
		${BOX2D_Rope_HDRS}
		${BOX2D_Api_SRCS}
		${BOX2D_Api_HDRS}
	)
	set_target_properties(Box2D_shared PROPERTIES
		OUTPUT_NAME "liquidfundll"
		CLEAN_DIRECT_OUTPUT 1
		VERSION ${BOX2D_VERSION}
	)

	if(UNIX AND NOT APPLE)
		target_link_libraries(Box2D_shared rt)
	endif(UNIX AND NOT APPLE)
endif()

if(BOX2D_BUILD_STATIC)
	add_library(Box2D STATIC
		${BOX2D_Unity_HDRS}
		${BOX2D_General_HDRS}
		${BOX2D_Joints_SRCS}
		${BOX2D_Joints_HDRS}
		${BOX2D_Contacts_SRCS}
		${BOX2D_Contacts_HDRS}
		${BOX2D_Dynamics_SRCS}
		${BOX2D_Dynamics_HDRS}
		${BOX2D_Common_SRCS}
		${BOX2D_Common_HDRS}
		${BOX2D_Shapes_SRCS}
		${BOX2D_Shapes_HDRS}
		${BOX2D_Collision_SRCS}
		${BOX2D_Collision_HDRS}
		${BOX2D_Particle_SRCS}
		${BOX2D_Particle_HDRS}
		${BOX2D_Rope_SRCS}
		${BOX2D_Rope_HDRS}
		${BOX2D_Api_SRCS}
		${BOX2D_Api_HDRS}
	)
	set_target_properties(Box2D PROPERTIES
		OUTPUT_NAME "liquidfundll"
		CLEAN_DIRECT_OUTPUT 1
		VERSION ${BOX2D_VERSION}
	)

	if(UNIX AND NOT APPLE)
		target_link_libraries(Box2D rt)
	endif(UNIX AND NOT APPLE)
endif()

# These are used to create visual studio folders.
source_group(Collision FILES ${BOX2D_Collision_SRCS} ${BOX2D_Collision_HDRS})
source_group(Collision\\Shapes FILES ${BOX2D_Shapes_SRCS} ${BOX2D_Shapes_HDRS})
source_group(Common FILES ${BOX2D_Common_SRCS} ${BOX2D_Common_HDRS})
source_group(Dynamics FILES ${BOX2D_Dynamics_SRCS} ${BOX2D_Dynamics_HDRS})
source_group(Dynamics\\Contacts FILES ${BOX2D_Contacts_SRCS} ${BOX2D_Contacts_HDRS})
source_group(Dynamics\\Joints FILES ${BOX2D_Joints_SRCS} ${BOX2D_Joints_HDRS})
source_group(Include FILES ${BOX2D_General_HDRS})
source_group(Particle FILES ${BOX2D_Particle_SRCS} ${BOX2D_Particle_HDRS})
source_group(Rope FILES ${BOX2D_Rope_SRCS} ${BOX2D_Rope_HDRS})
source_group(Api FILES ${BOX2D_Api_SRCS} ${BOX2D_Api_HDRS})

if(BOX2D_INSTALL)
	# install headers
	install(FILES ${BOX2D_General_HDRS} DESTINATION include/Box2D)
	install(FILES ${BOX2D_Collision_HDRS} DESTINATION include/Box2D/Collision)
	install(FILES ${BOX2D_Shapes_HDRS} DESTINATION include/Box2D/Collision/Shapes)
	install(FILES ${BOX2D_Common_HDRS} DESTINATION include/Box2D/Common)
	install(FILES ${BOX2D_Dynamics_HDRS} DESTINATION include/Box2D/Dynamics)
	install(FILES ${BOX2D_Contacts_HDRS} DESTINATION include/Box2D/Dynamics/Contacts)
	install(FILES ${BOX2D_Joints_HDRS} DESTINATION include/Box2D/Dynamics/Joints)
	install(FILES ${BOX2D_Particle_HDRS} DESTINATION include/Box2D/Particle)
	install(FILES ${BOX2D_Api_HDRS} DESTINATION include/Box2D/Api)
	install(FILES ${BOX2D_Rope_HDRS} DESTINATION include/Box2D/Rope)
	install(FILES ${BOX2D_Unity_HDRS} DESTINATION include/Box2D/Unity)

	# install libraries
	if(BOX2D_BUILD_SHARED)
		install(TARGETS Box2D_shared EXPORT Box2D-targets 
                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
                  RUNTIME DESTINATION bin)
	endif()
	if(BOX2D_BUILD_STATIC)
		install(TARGETS Box2D EXPORT Box2D-targets DESTINATION "${LIB_INSTALL_DIR}")
	endif()

	# install build system hooks for third-party apps
	install(EXPORT Box2D-targets DESTINATION "${LIB_INSTALL_DIR}/Box2D")

        set (BOX2D_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
        set (BOX2D_INCLUDE_DIRS "${BOX2D_INCLUDE_DIR}" )
        set (BOX2D_LIBRARY_DIRS "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")
        set (BOX2D_LIBRARY Box2D)
        set (BOX2D_LIBRARIES "${BOX2D_LIBRARY}")
        set (BOX2D_USE_FILE "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/cmake/Box2D/UseBox2D.cmake")
        configure_file(Box2DConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/Box2DConfig.cmake" @ONLY ESCAPE_QUOTES)
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Box2DConfig.cmake" UseBox2D.cmake DESTINATION "${LIB_INSTALL_DIR}/cmake/Box2D")
endif(BOX2D_INSTALL)
