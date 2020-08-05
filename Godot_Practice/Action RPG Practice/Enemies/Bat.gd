extends KinematicBody2D

const EnemyDeathEffect = preload("res://Effects/EnemyDeathEffect.tscn")

export var ACCELERATION = 250
export var MAX_SPEED = 45
export var FRICTION = 125
export var WANDER_TARGET_RANGE = 4

onready var sprite = $AnimatedSprite
onready var stats = $Stats
onready var playerDetectionZone = $PlayerDetectionZone
onready var hurtbox = $Hurtbox
onready var softCollision = $SoftCollision
onready var wanderController = $WanderController
onready var animationPlayer = $AnimationPlayer


var states = {
	"IDLE": funcref(self, "idle_state"),
	"WANDER": funcref(self, "wander_state"),
	"CHASE": funcref(self, "chase_state")
}

var current_state = "CHASE"

var velocity = Vector2.ZERO
var knockback = Vector2.ZERO

func _ready():
	randomize()
	stats.max_health = randi()%5+1
	stats.health = stats.max_health
	current_state = pick_rand_state(["IDLE", "WANDER"])

func _physics_process(delta):
	knockback = knockback.move_toward(Vector2.ZERO, FRICTION * delta)
	knockback = move_and_slide(knockback)
	
	states[current_state].call_func(delta)
	
	if softCollision.is_colliding():
		velocity += softCollision.get_push_vector() * delta * 250
	velocity = move_and_slide(velocity)

func idle_state(delta):
	velocity = velocity.move_toward(Vector2.ZERO, FRICTION * delta)
	seek_player()
	
	if wanderController.get_time_left() == 0:
		current_state = pick_rand_state(["IDLE", "WANDER"])
		wanderController.start_wander_timer(rand_range(2, 4))

func wander_state(delta):
	seek_player()
	
	if wanderController.get_time_left() == 0:
		current_state = pick_rand_state(["IDLE", "WANDER"])
		wanderController.start_wander_timer(rand_range(2, 4))
	
	accelerate_towards_point(wanderController.target_position, delta)
	
	if global_position.distance_to(wanderController.target_position) <= WANDER_TARGET_RANGE:
		current_state = pick_rand_state(["IDLE", "WANDER"])
		wanderController.start_wander_timer(rand_range(2, 4))

func chase_state(delta):
	var player = playerDetectionZone.player
	if player != null:
		accelerate_towards_point(player.global_position, delta)
	else:
		current_state = "IDLE"

func accelerate_towards_point(point, delta):
	var direction = global_position.direction_to(point)
	velocity = velocity.move_toward(direction * MAX_SPEED, ACCELERATION * delta)
	sprite.flip_h = velocity.x < 0
	

func seek_player():
	if playerDetectionZone.can_see_player():
		current_state = "CHASE"

func pick_rand_state(state_list):
	state_list.shuffle()
	return state_list.pop_front()

func _on_Hurtbox_area_entered(area):
	stats.health -= area.damage
	knockback = area.knockback_vector * 120
	hurtbox.create_hit_effect()
	hurtbox.apply_untargetable(0.25)

func _on_Stats_no_health():
	queue_free()
	var enemyDeathEffect = EnemyDeathEffect.instance()
	get_parent().add_child(enemyDeathEffect)
	enemyDeathEffect.global_position = global_position

func _on_Hurtbox_untargetable_applied():
	animationPlayer.play("Start")


func _on_Hurtbox_untargetable_faded():
	animationPlayer.play("Stop")
