arc = mx.get_scene("Sandbox").copy_object("py_arc", "Arc170")
arc.scale(0.01, 0.01, 0.01)
arc.move_up(1.0).move_forward(-10.0)
bind_shader("shaders/object_vertex.glsl", "shaders/object_fragment.glsl")