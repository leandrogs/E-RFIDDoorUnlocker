<div class="accesslogs view">
<h2><?php echo __('Accesslog'); ?></h2>
	<dl>
		<dt><?php echo __('Id'); ?></dt>
		<dd>
			<?php echo h($accesslog['Accesslog']['id']); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('Tagid'); ?></dt>
		<dd>
			<?php echo $this->Html->link($accesslog['Tagid']['id'], array('controller' => 'tagids', 'action' => 'view', $accesslog['Tagid']['id'])); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('User'); ?></dt>
		<dd>
			<?php echo $this->Html->link($accesslog['User']['id'], array('controller' => 'users', 'action' => 'view', $accesslog['User']['id'])); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('Created'); ?></dt>
		<dd>
			<?php echo h($accesslog['Accesslog']['created']); ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Edit Accesslog'), array('action' => 'edit', $accesslog['Accesslog']['id'])); ?> </li>
		<li><?php echo $this->Form->postLink(__('Delete Accesslog'), array('action' => 'delete', $accesslog['Accesslog']['id']), array(), __('Are you sure you want to delete # %s?', $accesslog['Accesslog']['id'])); ?> </li>
		<li><?php echo $this->Html->link(__('List Accesslogs'), array('action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('New Accesslog'), array('action' => 'add')); ?> </li>
		<li><?php echo $this->Html->link(__('List Tagids'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('New Tagid'), array('controller' => 'tagids', 'action' => 'add')); ?> </li>
		<li><?php echo $this->Html->link(__('List Users'), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('New User'), array('controller' => 'users', 'action' => 'add')); ?> </li>
	</ul>
</div>
