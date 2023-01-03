# Mohammed - Battleships

## Challenge Outline
I was tasked with designing, developing and testing a take on the classic Battleships game.
The idea was to allow a player to play against a CPU in accordance with the normal game rules.

### Game Mechanics

### Objective: 
Sink all of the opponent’s ships before they sink yours.

### Gameplay
Players will arrange their ships on the board horizontally or vertically and without any overlap. 
Players will take turns to fire missiles at a specified coordinate on the opponent’s board (e.g., B2) with the intention to hit an enemy ship. 
The attacking player will be notified whether it was a hit or miss. The game is won when one player has destroyed all the opposing ships completely.

My rendition includes:

* The simultaneous display of both the player’s and enemy’s boards
* Turn taking mechanism - boards are updated with each valid attack
* Error handling to deal with inappropriate user inputs
* Win/Loss/Tie detection and display
* The ability to quit at any time

## Initial Design

![Design UML](https://www.planttext.com/api/plantuml/png/fLPDKzim43tZNw7UJ2UTQQ-XPGWV8SnGcaa2XruombfYJMN98ya1skb_xqgsPJa9QJhbWYNjnzktJwkS6KkrhGgH99PR0UIhocbH02FdrE9wdlFI9CaxcqC1X3wR3qfJkO8aoGGrXfmhgXdvbPIQhwc5OK88bvOi3Vy99ycH_vO-2AwCPSFX6ZAhzEVusmTPS06dfsJvw1ORnYx0UpmpJQ17fGHPKy4Pvfmgate3OewRb0Ai1RrG5qffbcOvrUJ5dQqLPuGovimNogUDNPEoUXGy6oP7zP4BvGeXNyZbrNXqVxjOddyRpIxdDz-l1hxEkhJe_6u-kPdEGoxaYgbYgifA8DAqnRS2wpFCCNXwJ38bZMrTJ7pM8ZXk2J5MSxaYZ9jIqDSQvXk74yuOoCx4ayRDM03OIq1RzGhHISvj6dEEgKyH6HBekQbfGk3kOsGzisQVGsYgStB_3t3wtShA9ObLrQlFo-2E5a5W0kJAvcqXopLeopCgDaJaKothNAqd5kswzp7uifOOt7sYma1F5WvM6aEHYA9M0c8Oa5gNJVe1sSEERtMJB0qRhWURtKJsNArn2tTqZvk79cqiiWcMrmMCaU1Xqut8_DRp6EzSg5wycNfEupPrFVxLaLGJ2KLfNv54goi8ybbcbTOWlOO2vLXqHtO8VOqrJ_3s2D1U2CeYUc33NJsLyD9Kq-eEKnNrxOXsG4AtsU6DCgMDQMCs8CswyyJgiLSSHoOLs_rrlK8i8sjfzWCljbTMA6cAbn9qMnJQWMJRXRQAtpF7Ekoza0UXFnpy4vVk3WNu5zFxls1lK17ywumFGkLS_XMOyzbbEvEiatPFJpr-MrMKdi9zMkb997YSR6vx5oyFF_ahkQYqJBrWwcVGhPjX4zx8NKzB_ztSUbp2nU5c3lQ-Z2PLkp-hf7IpO_jap2KtUJpU-XVX_zwyU6wXgLPRqwm0MRtrOBdyddBpbiNOTRup2NFfmVqKk95bPJt-WhxKK0lk2F_aJJq3-BXMvNLld6AZ-Xlu6jjs1-LpXah7tqT_0000)
