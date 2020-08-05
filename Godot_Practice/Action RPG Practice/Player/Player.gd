extends KinematicBody2D

const PlayerHurtSound = preload("res://Player/PlayerHurtSound.tscn")

export var ACCELERATION = 400
export var MAX_SPEED = 120
var FRICTION = ACCELERATION * 0.85
export var ROLL_SPEED = 130

var velocity = Vector2.ZERO
var input_vector = Vector2.ZERO
var roll_vector = Vector2.DOWN
var stats = PlayerStats

onready var animationPlayer = $AnimationPlayer
onready var animationTree = $AnimationTree
onready var animationState = animationTree.get("parameters/playback")
onready var swordHitbox = $HitboxPivot/SwordHitbox
onready var hurtbox = $Hurtbox
onready var blinkAnimationPlayer = $BlinkAnimationPlayer

var states = {
	"MOVE": funcref(self, "move_state"),
	"ATK": funcref(self, "attack_state"),
	"ROLL": funcref(self, "roll_state"),
}
var current_state = "MOVE"
var is_able_to_act = true

func _ready():
	stats.connect("no_health", self, "queue_free")
	animationTree.active = true
	swordHitbox.knockback_vector = roll_vector

func _physics_process(delta):
	input_vector = Vector2.ZERO
	input_vector.x = Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left")
	input_vector.y = Input.get_action_strength("ui_down") - Input.get_action_strength("ui_up")
	input_vector = input_vector.normalized()
	
	if input_vector != Vector2.ZERO:
		velocity = velocity.move_toward(input_vector * MAX_SPEED, ACCELERATION * delta)
	else:
		velocity = velocity.move_toward(Vector2.ZERO, FRICTION * delta)
	
	states[current_state].call_func()
	
	velocity = move_and_slide(velocity)
	
	if is_able_to_act:
		if Input.is_action_just_pressed("attack"):
			current_state = "ATK"
		elif Input.is_action_just_pressed("roll"):
			current_state = "ROLL"

func move_state():
	if input_vector != Vector2.ZERO:
		roll_vector = input_vector
		swordHitbox.knockback_vector = input_vector
		animationTree.set("parameters/Idle/blend_position", input_vector)
		animationTree.set("parameters/Run/blend_position", input_vector)
		animationTree.set("parameters/Attack/blend_position", input_vector)
		animationTree.set("parameters/Roll/blend_position", input_vector)
		animationState.travel("Run")
	else:
		animationState.travel("Idle")

func attack_state():
	animationState.travel("Attack")
	is_able_to_act = false

func roll_state():
	velocity = roll_vector * ROLL_SPEED
	animationState.travel("Roll")
	is_able_to_act = false

func attack_animation_finished():
	current_state = "MOVE"
	is_able_to_act = true

func roll_animation_finished():
	current_state = "MOVE"
	is_able_to_act = true

func _on_Hurtbox_area_entered(area):
	stats.health -= area.damage
	hurtbox.apply_untargetable(0.7)
	hurtbox.create_hit_effect()
	var playerHurtSound = PlayerHurtSound.instance()
	get_tree().current_scene.add_child(playerHurtSound)

func _on_Hurtbox_untargetable_applied():
	blinkAnimationPlayer.play("Start")

func _on_Hurtbox_untargetable_faded():
	blinkAnimationPlayer.play("Stop")
