extends Area2D

const HitEffect = preload("res://Effects/HitEffect.tscn")

var untargetable = false setget set_untargetable

onready var timer = $Timer
onready var collisionShape = $CollisionShape2D

signal untargetable_applied
signal untargetable_faded

func set_untargetable(value):
	untargetable = value
	if untargetable == true:
		emit_signal("untargetable_applied")
	else:
		emit_signal("untargetable_faded")

func apply_untargetable(duration):
	self.untargetable = true
	timer.start(duration)

func create_hit_effect():
	var effect = HitEffect.instance()
	var main = get_tree().current_scene
	main.add_child(effect)
	effect.global_position = global_position

func _on_Timer_timeout():
	self.untargetable = false

func _on_Hurtbox_untargetable_applied():
	collisionShape.set_deferred("disabled", true)

func _on_Hurtbox_untargetable_faded():
	collisionShape.disabled = false
