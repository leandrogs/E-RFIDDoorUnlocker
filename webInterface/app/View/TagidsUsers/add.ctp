<div class="tagidsUsers form">
<?php echo $this->Form->create('TagidsUser'); ?>
	<fieldset>
		<legend><?php echo __('Add Tagids User'); ?></legend>
	<?php
		// echo $this->Form->hidden('tagid', array('value' => 'Tag ID'));
		// echo $this->Form->hidden('user', array('value' => 'Usuário'));
		echo $this->Form->input('tagid_id', array('label' => 'Tag ID'));
		echo $this->Form->input('user_id', array('label' => 'Usuário'));
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit')); ?>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Usuários/Tag'), array('action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Tags'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Listar Usuários'), array('controller' => 'users', 'action' => 'index')); ?> </li>
	</ul>
</div>
