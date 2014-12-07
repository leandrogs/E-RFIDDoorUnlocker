<div class="users form">
<?php echo $this->Form->create('User'); ?>
	<fieldset>
		<legend><?php echo __('Add User'); ?></legend>
	<?php
		echo $this->Form->input('username', array('label' => 'Nome de usuário'));
		echo $this->Form->input('password', array('label' => 'Senha'));
		echo $this->Form->input('email');
		echo $this->Form->input('role', array('label' => 'Admin', 'type' => 'checkbox'));
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit')); ?>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Usuários'), array('action' => 'index')); ?></li>
	</ul>
</div>
